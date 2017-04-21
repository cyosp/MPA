// 2017-04-21 V 1.8.0
// - Remove: Administrator account at the end of test
// 2017-04-16 V 1.7.0
// - Add: Create a category
// 2017-02-23 V 1.6.0
// - Add: Get list of locales
// - User creation is now performed with a locale
// 2017-02-14 V 1.5.0
// - Add: Create an account
// 2017-02-12 V 1.4.0
// - Add: delete user
// 2017-02-11 V 1.3.0
// - Manage add a non administrator user
// 2017-02-07 V 1.2.0
// - Manage logout
// 2017-01-15 V 1.1.1
// - Update to new URL API
// 2017-01-13 V 1.1.0
// - Manage register administrator account
// 2017-01-08 V 1.0.0
// - First version

var chai      = require("chai");
var request   = require("request");

var expect    = chai.expect;
var assert    = chai.assert;

chai.use( require("chai-http") );
chai.use( require('chai-json-schema') );

var host = "http://localhost:8080";
var adminLogin = "cyosp";
var adminPwd = "CYOSP1";
var userAdminId = null;
var adminVersion = null;
var adminToken = null;
var defaultLocale = "";

var adminLoginFct = function()
{
	describe( "Administrator login" , function()
	{
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/login" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: adminLogin , pwd: adminPwd } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
					userAdminData = data;

					// End test
		    		done();
				}
		  	});
		});
	
		it( "token is a number" , function( done )
		{
			// Check JSON contains id property
			assert.property( userAdminData , 'id' );

			// Get token
			adminToken = userAdminData.id;
			
			// Check token is a number
			expect( adminToken , 'token is not a number' ).to.be.not.NaN;
			
			// End test
			done();
		});
	});
}

var adminLogoutFct = function()
{
	describe( "Administrator logout" , function()
	{
		var userAdminData;
		var logoutId;

		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/users/logout?token=" + adminToken )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send()
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			userAdminData = data;

					// End test
		    		done();
				}
		  	});
		});
		it( "execution code is equal to 0" , function( done )
		{
			// Check JSON contains id property
			assert.property( userAdminData , 'id' );

			// Get id
			logoutId = userAdminData.id;

			expect( logoutId , 'execution code is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
}

describe( "MPA API" , function()
{
	describe( "Get list of locales" , function()
	{
		var localesData = null;
		
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/locales" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send()
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		
					// Get response data
		   			localesData = data;

					// End test
		    		done();
				}
		  	});
		});
		it( "locales is an non empty array" , function( done )
		{
			// Check JSON contains locales property
			assert.property( localesData , 'locales' );
			
			// Check locales is an array
			expect( localesData.locales , 'locales is not an array' ).to.be.instanceof(Array);
			
			// Check array is not empty
			expect( localesData.locales , 'locales array is empty' ).to.be.not.empty;
			
			// End test
			done();
		});
		it( "get first locale" , function( done )
		{
			// Check JSON contains name property
			assert.property( localesData.locales[0] , 'name' );
			
			// Check locale name is not empty
			expect( localesData.locales[0].name , 'locale name is empty' ).to.be.not.empty;
			
			// Get default locale
			defaultLocale = localesData.locales[0].name;
			
			// End test
			done();
		});
	});
	
	describe( "Register administrator account" , function()
	{
		var userAdminData = null;
		
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: adminLogin , password: adminPwd , passwordConfirm: adminPwd, locale: defaultLocale } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		
					// Get response data
					userAdminData = data;

					// End test
		    		done();
				}
		  	});
		});
		it( "identifier is a positive number" , function( done )
		{
			// Check JSON contains id property
			assert.property( userAdminData , 'id' );
			
			// Check administrator user id is a number
			expect( userAdminData.id , 'identifier is not a number' ).to.be.not.NaN;
			
			userAdminId = parseInt( userAdminData.id );
			
			// Check administrator user is a positive number
			expect( Math.abs( userAdminId ) ).to.be.equal( userAdminId );
			
			// End test
			done();
		});
		it( "version is equal to 0" , function( done )
		{
			// Check JSON contains version property
			assert.property( userAdminData , 'version' );
			
			adminVersion = userAdminData.version;
			
			// Check version is equal to 0
			expect( adminVersion , 'version is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});

	adminLoginFct();
	
	var userLogin = "user";
	var userPwd = "PASSWORD1";
	var userId = null;
	var userVersion = null;
	
	describe( "Create a user" , function()
	{
		var userData = null;
		
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: userLogin , password: userPwd , passwordConfirm: userPwd, token: adminToken, locale: defaultLocale } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			userData = data;

					// End test
		    		done();
				}
		  	});
		});
		it( "identifier is a positive number" , function( done )
		{
			// Check JSON contains id property
			assert.property( userData , 'id' );

			// Get token
			userId = userData.id;
			
			// Check user id is a number
			expect( userId , 'identifier is not a number' ).to.be.not.NaN;
			
			userId = parseInt( userId );
			
			// Check user is a positive number
			expect( Math.abs( userId ) ).to.be.equal( userId );
			
			// End test
			done();
		});
		it( "version is equal to 0" , function( done )
		{
			// Check JSON contains version property
			assert.property( userData , 'version' );
			
			// Get version
			userVersion = userData.version;
			
			expect( userVersion , 'version is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
	
	var accountId = null;
	describe( "Create an account" , function()
	{
		var accountData = null;
		
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/accounts/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {name: "MyBank", token: adminToken } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );

					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			accountData = data;

					// End test
		    		done();
				}
		  	});
		});
		it( "identifier is a positive number" , function( done )
		{
			// Check JSON contains id property
			assert.property( accountData , 'id' );

			// Get id
			accountId = accountData.id;
			
			// Check account id is a number
			expect( accountId , 'identifier is not a number' ).to.be.not.NaN;
			
			accountId = parseInt( accountId );
			
			// Check account is a positive number
			expect( Math.abs( accountId ) ).to.be.equal( accountId );
			
			// End test
			done();
		});
		it( "version is equal to 0" , function( done )
		{
			// Check JSON contains version property
			assert.property( accountData , 'version' );
			
			expect( accountData.version , 'version is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
		it( "balance is equal to 0" , function( done )
		{
			// Check JSON contains balance property
			assert.property( accountData , 'balance' );
			
			expect( accountData.balance , 'balance is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
	
	var categoryId = null;
	describe( "Create a category" , function()
	{
		var categoryData = null;
		
		
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/accounts/" + accountId + "/categories/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {name: "MyCategory", token: adminToken } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );

					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			categoryData = data;

					// End test
		    		done();
				}
		  	});
		});
		it( "identifier is a positive number" , function( done )
		{
			// Check JSON contains id property
			assert.property( categoryData , 'id' );

			// Get id
			categoryId = categoryData.id;
			
			// Check category id is a number
			expect( categoryId , 'identifier is not a number' ).to.be.not.NaN;
			
			categoryId = parseInt( categoryId );
			
			// Check category is a positive number
			expect( Math.abs( categoryId ) ).to.be.equal( categoryId );
			
			// End test
			done();
		});
		it( "version is equal to 0" , function( done )
		{
			// Check JSON contains version property
			assert.property( categoryData , 'version' );
			
			expect( categoryData.version , 'version is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
		

		it( "amount is equal to 0" , function( done )
		{
			// Check JSON contains amount property
			assert.property( categoryData , 'amount' );
			
			expect( categoryData.amount , 'amount is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
	
	adminLogoutFct();
	
	describe( "User login" , function()
	{
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/login" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: userLogin , pwd: userPwd } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
					userData = data;

					// End test
		    		done();
				}
		  	});
		});
	
		it( "token is a number" , function( done )
		{
			// Check JSON contains id property
			assert.property( userData , 'id' );

			// Get token
			userToken = userData.id;
			
			// Check token is a number
			expect( userToken , 'token is not a number' ).to.be.not.NaN;
			
			// End test
			done();
		});
	});
	
	describe( "User logout" , function()
	{
		var userData;
		var logoutId;

		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/users/logout?token=" + userToken )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send()
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			userData = data;

					// End test
		    		done();
				}
		  	});
		});
		it( "execution code is equal to 0" , function( done )
		{
			// Check JSON contains id property
			assert.property( userData , 'id' );

			// Get id
			logoutId = userData.id;

			expect( logoutId , 'execution code is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
	
	adminLoginFct();
	
	describe( "Delete user" , function()
	{
		var userData = null;
		
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/" + userId + "/del" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {version: userVersion , token: adminToken } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// get response data
		   			userData = data;

					// End test
		    		done();
				}
		  	});
		});
		
		it( "execution code is equal to 0" , function( done )
		{
			// Check JSON contains id property
			assert.property( userData , 'id' );

			// Get token
			userId = userData.id;
			
			expect( userId , 'execution code is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
	
	describe( "Delete administrator" , function()
	{
		var adminData = null;
		
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/" + userAdminId + "/del" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {version: adminVersion , token: adminToken } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// get response data
		   			adminData = data;

					// End test
		    		done();
				}
		  	});
		});
		
		it( "execution code is equal to 0" , function( done )
		{
			// Check JSON contains id property
			assert.property( adminData , 'id' );

			// Get token
			adminId = adminData.id;
			
			expect( adminId , 'execution code is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
	
	adminLogoutFct();
});

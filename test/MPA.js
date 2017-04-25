// 2017-04-25 V 1.13.0
// - Add: Remove account
// 2017-04-25 V 1.12.0
// - Add: Remove category
// 2017-04-25 V 1.11.0
// - Add: Remove account
// 2017-04-25 V 1.10.0
// - Add: Get list of accounts
// 2017-04-23 V 1.9.0
// - Add: Get list of users
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

// Allow to display REST API responses
var DEBUG_MODE = true;

var chai      = require("chai");
var request   = require("request");

var expect    = chai.expect;
var assert    = chai.assert;

var debug = function( message )
{
	if( DEBUG_MODE )	console.log( message );		
}

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
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/login" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: adminLogin , pwd: adminPwd } )
			.end( function( error , response , body )
			{
				debug( response.text );

				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
					userAdminData = data;
					
					// Check JSON contains id property
					assert.property( userAdminData , 'id' );
					
					// Get token
					adminToken = userAdminData.id;
					
					// Check token is a number
					expect( adminToken , 'token is not a number' ).to.be.not.NaN;

					// End test
		    		done();
				}
		  	});
		});
	});
}

var adminLogoutFct = function()
{
	describe( "Administrator logout" , function()
	{
		var userAdminData;
		var logoutId;

		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/users/logout?token=" + adminToken )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send()
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			userAdminData = data;
		   			
		   			// Check JSON contains id property
					assert.property( userAdminData , 'id' );

					// Get id
					logoutId = userAdminData.id;

					expect( logoutId , 'execution code is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
		});
	});
}

describe( "MPA API" , function()
{
	describe( "Get list of locales" , function()
	{		
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/locales" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send()
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
		   			expect( response.statusCode ).to.equal(200);
		   			expect( data ).to.have.deep.property( 'locales[0].name' );
					
					// Get default locale
					defaultLocale = data.locales[0].name;

					// End test
		    		done();
				}
		  	});
		});
	});
	
	describe( "Register administrator account" , function()
	{
		var userAdminData = null;
		
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: adminLogin , password: adminPwd , passwordConfirm: adminPwd, locale: defaultLocale } )
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		
					// Get response data
					userAdminData = data;
					
					// Check JSON contains id property
					assert.property( userAdminData , 'id' );
					
					// Check administrator user id is a number
					expect( userAdminData.id , 'identifier is not a number' ).to.be.not.NaN;
					
					userAdminId = parseInt( userAdminData.id );
					
					// Check administrator user is a positive number
					expect( Math.abs( userAdminId ) ).to.be.equal( userAdminId );
					
					// Check JSON contains version property
					assert.property( userAdminData , 'version' );
					
					adminVersion = userAdminData.version;
					
					// Check version is equal to 0
					expect( adminVersion , 'version is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
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
		
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: userLogin , password: userPwd , passwordConfirm: userPwd, token: adminToken, locale: defaultLocale } )
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			userData = data;
		   			
		   			// Check JSON contains id property
					assert.property( userData , 'id' );

					// Get token
					userId = userData.id;
					
					// Check user id is a number
					expect( userId , 'identifier is not a number' ).to.be.not.NaN;
					
					userId = parseInt( userId );
					
					// Check user is a positive number
					expect( Math.abs( userId ) ).to.be.equal( userId );
					
					// Check JSON contains version property
					assert.property( userData , 'version' );
					
					// Get version
					userVersion = userData.version;
					
					expect( userVersion , 'version is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
		});
	});
	
	describe( "Get list of users" , function()
	{
		var usersData = null;
		
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/users?token=" + adminToken )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send()
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		
					// Get response data
		   			usersData = data;
		   			
		   			expect( usersData , adminLogin +  " is not in the list" ).to.have.deep.property( 'users[0].login' , adminLogin );
					expect( usersData , userLogin  +  " is not in the list" ).to.have.deep.property( 'users[1].login' , userLogin );
					
					expect( usersData ).to.have.deep.property( 'users[0].version' , '0' );
					expect( usersData ).to.have.deep.property( 'users[0].isAdmin' , 'true' );
					expect( usersData ).to.have.deep.property( 'users[0].pwdErrNbr' , '0' );
					
					expect( usersData ).to.have.deep.property( 'users[1].version' , '0' );
					expect( usersData ).to.have.deep.property( 'users[1].isAdmin' , 'false' );
					expect( usersData ).to.have.deep.property( 'users[1].pwdErrNbr' , '0' );

					// End test
		    		done();
				}
		  	});
		});
	});
	
	var accountId = null;
	var accountVersion = null;
	var accountName = "MyBank";
	describe( "Create an account" , function()
	{
		var accountData = null;
		
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/accounts/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {name: accountName, token: adminToken } )
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );

					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			accountData = data;
		   			
		   			// Check JSON contains id property
					assert.property( accountData , 'id' );

					// Get id
					accountId = accountData.id;
					
					// Check account id is a number
					expect( accountId , 'identifier is not a number' ).to.be.not.NaN;
					
					accountId = parseInt( accountId );
					
					// Check account is a positive number
					expect( Math.abs( accountId ) ).to.be.equal( accountId );
					
					// Check JSON contains version property
					assert.property( accountData , 'version' );
					
					accountVersion = accountData.version;
					
					expect( accountVersion , 'version is not equal to 0' ).to.be.equal( "0" );
					
					// Check JSON contains balance property
					assert.property( accountData , 'balance' );
					
					expect( accountData.balance , 'balance is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
		});
	});
	
	describe( "Get list of accounts" , function()
	{
		var accountsData = null;
		
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/accounts?token=" + adminToken )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send()
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		
					// Get response data
		   			accountsData = data;
					
					expect( accountsData ).to.have.deep.property( 'accounts[0].version' , '0' );
					expect( accountsData ).to.have.deep.property( 'accounts[0].name' , accountName );
					expect( accountsData ).to.have.deep.property( 'accounts[0].balance' , '0' );

					// End test
		    		done();
				}
		  	});
		});
	});
	
	var categoryId = null;
	var categoryName = "MyCategory";
	var categoryVersion = null;
	describe( "Create a category" , function()
	{
		var categoryData = null;
		
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/accounts/" + accountId + "/categories/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {name: categoryName, token: adminToken } )
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );

					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			categoryData = data;
		   			
		   			// Check JSON contains id property
					assert.property( categoryData , 'id' );

					// Get id
					categoryId = categoryData.id;
					
					// Check category id is a number
					expect( categoryId , 'identifier is not a number' ).to.be.not.NaN;
					
					categoryId = parseInt( categoryId );
					
					// Check category is a positive number
					expect( Math.abs( categoryId ) ).to.be.equal( categoryId );
					
					// Check JSON contains version property
					assert.property( categoryData , 'version' );
					
					// Get category version
					categoryVersion = categoryData.version;
					
					expect( categoryVersion , 'version is not equal to 0' ).to.be.equal( "0" );
					
					// Check JSON contains amount property
					assert.property( categoryData , 'amount' );
					
					expect( categoryData.amount , 'amount is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
		});
	});
	
	adminLogoutFct();
	
	describe( "User login" , function()
	{
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/login" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: userLogin , pwd: userPwd } )
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
					userData = data;
					
					// Check JSON contains id property
					assert.property( userData , 'id' );

					// Get token
					userToken = userData.id;
					
					// Check token is a number
					expect( userToken , 'token is not a number' ).to.be.not.NaN;

					// End test
		    		done();
				}
		  	});
		});
	});
	
	describe( "User logout" , function()
	{
		var userData;
		var logoutId;

		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/users/logout?token=" + userToken )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send()
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Get response data
		   			userData = data;
		   			
		   			// Check JSON contains id property
					assert.property( userData , 'id' );

					// Get id
					logoutId = userData.id;

					expect( logoutId , 'execution code is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
		});
	});
	
	adminLoginFct();
	
	describe( "Delete user" , function()
	{
		var userData = null;
		
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/" + userId + "/del" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {version: userVersion , token: adminToken } )
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// get response data
		   			userData = data;
		   			
		   			// Check JSON contains id property
					assert.property( userData , 'id' );

					// Get token
					userId = userData.id;
					
					expect( userId , 'execution code is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
		});
	});
	
	describe( "Delete category" , function()
	{	
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/accounts/" + accountId + "/categories/" + categoryId + "/del" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {version: categoryVersion , token: adminToken } )
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Check JSON contains id property
					assert.property( data , 'id' );
					
					expect( data.id , 'execution code is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
		});
	});
	
	describe( "Delete account" , function()
	{	
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/accounts/" + accountId + "/del" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {version: accountVersion , token: adminToken } )
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// Check JSON contains id property
					assert.property( data , 'id' );
					
					expect( data.id , 'execution code is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
		});
	});

	describe( "Delete administrator" , function()
	{
		var adminData = null;
		
		it( "check response integrity" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/" + userAdminId + "/del" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {version: adminVersion , token: adminToken } )
			.end( function( error , response , body )
			{
				debug( response.text );
				
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
		   			// get response data
		   			adminData = data;
		   			
		   			// Check JSON contains id property
					assert.property( adminData , 'id' );

					// Get token
					adminId = adminData.id;
					
					expect( adminId , 'execution code is not equal to 0' ).to.be.equal( "0" );

					// End test
		    		done();
				}
		  	});
		});
	});
	
	adminLogoutFct();
});

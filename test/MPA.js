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
var adminToken = null;

describe( "MPA API" , function()
{
	describe( "Register administrator account" , function()
	{
		var userAdminData = null;
		
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: adminLogin , password: adminPwd , passwordConfirm: adminPwd } )
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
			
			var userAdminId = parseInt( userAdminData.id );
			
			// Check administrator user is a positive number
			expect( Math.abs( userAdminId ) ).to.be.equal( userAdminId );
			
			// End test
			done();
		});
		it( "version is equal to 0" , function( done )
		{
			// Check JSON contains version property
			assert.property( userAdminData , 'version' );
			
			// Check version is equal to 0
			expect( userAdminData.version , 'version is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});

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
				.send( {login: userLogin , password: userPwd , passwordConfirm: userPwd, token: adminToken } )
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
	
	describe( "Create an account" , function()
	{
		var accountData = null;
		var accountId = null;
		
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
});

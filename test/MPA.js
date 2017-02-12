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
var token = null;

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
		   			
					// Check JSON contains id property
					assert.property( data , 'id' );
		
					// Get token
					token = data.id;

					// End test
		    		done();
				}
		  	});
		});
	
		it( "token is a number" , function( done )
		{
			// Check token is a number
			expect( token , 'token is not a number' ).to.be.not.NaN;
			
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
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/add" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: userLogin , password: userPwd , passwordConfirm: userPwd, token: token } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
					// Check JSON contains id property
					assert.property( data , 'id' );
		
					// Get token
					userId = data.id;
					// Get version
					userVersion = data.version;

					// End test
		    		done();
				}
		  	});
		});
		it( "identifier is a positive number" , function( done )
		{
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
			expect( userVersion , 'version is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
	
	describe( "Delete user" , function()
	{
		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.post( "/api/rest/v1/users/" + userId + "/del" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {version: userVersion , token: token } )
			.end( function( error , response , body )
			{
				if( error )	done( error );
				else
				{
					var data = JSON.parse( response.text );
					
					// Check response is 200
		   			expect( response.statusCode ).to.equal(200);
		   			
					// Check JSON contains id property
					assert.property( data , 'id' );
		
					// Get token
					userId = data.id;

					// End test
		    		done();
				}
		  	});
		});
		
		it( "execution code is equal to 0" , function( done )
		{
			expect( userId , 'execution code is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
	
	describe( "Administrator logout" , function()
	{
		var logoutId;

		it( "response code is equal to 200" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/users/logout?token=" + token )
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
		   			
					// Check JSON contains id property
					assert.property( data , 'id' );
		
					// Get id
					logoutId = data.id;

					// End test
		    		done();
				}
		  	});
		});
	
		it( "execution code is equal to 0" , function( done )
		{
			expect( logoutId , 'execution code is not equal to 0' ).to.be.equal( "0" );
			
			// End test
			done();
		});
	});
});

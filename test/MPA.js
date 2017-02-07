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
var token = null;

describe( "MPA API" , function()
{
	describe( "Register administrator account" , function()
	{
		it( "returns user identifier" , function( done )
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
		   			
					// Check JSON contains id property
					assert.property( data , 'id' );
		
					// Get token
					userAdminId = data.id;

					// End test
		    		done();
				}
		  	});
		});
		
		it( "identifier is a positive number" , function( done )
		{
			// Check administrator user id is a number
			expect( userAdminId , 'identifier is not a number' ).to.be.not.NaN;
			
			userAdminId = parseInt( userAdminId );
			
			// Check administrator user is a positive number
			expect( Math.abs( userAdminId ) ).to.be.equal( userAdminId );
			
			// End test
			done();
		});
	});

	describe( "Login" , function()
	{
		it( "returns token" , function( done )
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
	
	describe( "Logout" , function()
	{
		it( "log out" , function( done )
		{
			chai.request( host )
				.get( "/api/rest/v1/users/logout" )
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
});

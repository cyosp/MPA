// 2017-01-08 V 1.0.0
// - First version

var chai      = require("chai");
var request   = require("request");

var expect    = chai.expect;
var assert    = chai.assert;

chai.use( require("chai-http") );
chai.use( require('chai-json-schema') );

var host = "http://localhost:8080";
var token = null;

describe( "MPA API" , function()
{
	describe( "Login" , function()
	{
		it( "returns token" , function( done )
		{
			chai.request( host )
				.post( "/mpa/res/users/login" )
				.set( 'content-type', 'application/x-www-form-urlencoded' )
				.send( {login: 'cyosp' , pwd: 'CYOSP1' } )
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

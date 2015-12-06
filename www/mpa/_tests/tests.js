function runTests()
{
	var account1 = { name: "Mon compte 1 accentué" , id: "" , version: "", amount: "" };

	//
	// Add accounts tests
	//
	addAccount( account1 , { name: "Add account: '" + account1.name + "'" , errorWhichIsValid: "" } );
	addAccount( account1 , { name: "Fail to add account because already existing: '" + account1.name + "'" , errorWhichIsValid: "Un compte avec le même nom existe déjà" } );
	
	//
	// Update account tests
	//
	var account1NewName = "Mon compte 1 en compte 2";
	// Backup account id and version number
	var account1Id = account1.id;
	var account1Version = account1.version;
	// Set an invalid account id
	account1.id = -1;
	updateAccount(  account1 , { name: "Fail to update account '" + account1.name +"' name in '" + account1NewName + "' because URL is not correct: id is negative", errorWhichIsValid: "URL conversion failure" } , account1NewName );
	// Restore valid account id
	account1.id = account1Id;
	// Set an invalid version number
	account1.version = -1;
	updateAccount(  account1 , { name: "Fail to update account '" + account1.name +"' name in '" + account1NewName + "' because version is not the latest one", errorWhichIsValid: "Opération impossible car les données ont changé depuis leur récupération" } , account1NewName );
	// Restore valid version number
	account1.version = account1Version;
	updateAccount(  account1 , { name: "Update '" + account1.name +"' name in '" + account1NewName + "'", errorWhichIsValid: "" } , account1NewName );
	
	//
	// Delete account tests
	//
	delAccount( account1 , { name: "Delete account: '" + account1.name + "'" , errorWhichIsValid: "" } );
	
	
	
	
	/*for (i = 0; i < 100; i++)
	{
		var account = { name: "Mon compte: " + i , id: "" , version: "", amount: "" };
		addAccount( account , { name: "Add account: " + account1.name , errorWhichIsValid: "" } );
	}*/
	
}

//
// Display the result of test in the HTML page
//
function displayTestResult( testDetails , testReport , testResult )
{	
	var rowData =  '<div class="row">';
		rowData += '<div class="col-md-9 col-xs-4">' + testDetails + '</div>';
		rowData += '<div class="col-md-2 col-xs-4">' + testReport + '</div>';
		rowData += '<div class="col-md-1 col-xs-4 ' + testResult + 'Result">' + testResult + '</div>';
		rowData += '</div>';

	// Insert in DOM
	if( $("#mpaTestResults div.row").length == 0 )	$("#mpaTestResults").html(rowData);
	else											$(rowData).insertAfter($("#mpaTestResults div.row:last"));
	
	// Add color one line on two
	var lastRow = $("#mpaTestResults div.row:last");
	if( $("#mpaTestResults div.row").length % 2 === 0 )	lastRow.addClass( "peer" );
	else	lastRow.addClass( "odd" );
}

//
// Try to add an account
//
function addAccount( accountObject, testObject )
{	
	$.ajax({
	  type:  'POST',
	  url:   '../res/accounts/0/add',
	  data:  {name : accountObject.name, token : mpaToken},
	  async: false
	}).done(function(data)
	{
		var response = jQuery.parseJSON(data);
		var accountId = response.id;

		// Error in addind account
		if( isNaN(parseInt(accountId, 16)) )
		{
			if( accountId == testObject.errorWhichIsValid )	displayTestResult( testObject.name , "" , true );
			else											displayTestResult( testObject.name , accountId , false );
		}
		else
		{
			accountObject.id = accountId;
			accountObject.version = response.version;
			displayTestResult( testObject.name , "Account id: " + accountObject.id + ", version: " + accountObject.version , true );
		}
	}).fail(function() {
		displayTestResult( testObject.name , "Post fail" , false );
	})
}

//
// Try to delete an account
//
function delAccount( accountObject, testObject )
{
	$.ajax({
		  type:  'POST',
		  url:   '../res/accounts/' + accountObject.id + '/del',
		  data:  {version: accountObject.version, token : mpaToken},
		  async: false
	}).done(function(data)
	{
		// Get JSON response
		var response = jQuery.parseJSON(data);
		// Get account ID from response
		var accountId = response.id;

		// Error in deleting account
		if( isNaN( parseInt( accountId , 16 ) ) )	displayTestResult( testObject.name , accountId , false );
		else										displayTestResult( testObject.name , "", true );

	}).fail(function() {
		displayTestResult( testObject.name , "Post fail" , false );
	})
}

//
// Try to rename an account
//
function updateAccount( accountObject, testObject, newName )
{
	$.ajax({
		  type:  'POST',
		  url:   '../res/accounts/' + accountObject.id + '/upd',
		  data:  {name : newName, version: accountObject.version, token : mpaToken},
		  async: false
	}).done(function(data)
	{
		var response = jQuery.parseJSON(data);
		var accountId = response.id;

		// Error in addind account
		if( isNaN(parseInt(accountId, 16)) )
		{
			if( accountId == testObject.errorWhichIsValid )	displayTestResult( testObject.name , "" , true );
			else											displayTestResult( testObject.name , accountId , false );
		}
		else
		{
			accountObject.name = newName;
			accountObject.version = response.version;
			displayTestResult( testObject.name , "Version: " + accountObject.version, true );
		}
	}).fail(function() {
		displayTestResult( testObject.name , "Post fail" , false );
	})
}

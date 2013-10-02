<?php
/**
 * @file
 * wrappers for zend functions and direct interraction with google apis.
 */

$inc_path = get_include_path();
if (!in_array(dirname(__FILE__), explode(PATH_SEPARATOR, $inc_path))) {
  set_include_path(dirname(__FILE__) . PATH_SEPARATOR . $inc_path);
}

/**
 * Loads Zend_Loader class.
 */
require_once 'Zend/Loader.php';
/**
 * Loads Zend_Gdata class.
 */
Zend_Loader::loadClass('Zend_Gdata', dirname(__FILE__));

/**
 * Loads Zend_Gdata_AuthSub class.
 */
Zend_Loader::loadClass('Zend_Gdata_AuthSub', dirname(__FILE__));

/**
 * Loads Zend_Gdata_ClientLogin class.
 */
Zend_Loader::loadClass('Zend_Gdata_ClientLogin', dirname(__FILE__));

/**
 * Loads Zend_Gdata_Docs class.
 */
Zend_Loader::loadClass('Zend_Gdata_Docs', dirname(__FILE__));

Zend_Loader::loadClass('Zend_Http_Client', dirname(__FILE__));
Zend_Loader::loadClass('Zend_Gdata_Gapps', dirname(__FILE__));

/**
 * Returns a HTTP client object.
 *
 * Returns a HTTP client object with the appropriate headers for communicating
 * with Google using the ClientLogin credentials supplied.
 *
 * @param string $user
 *   A string that is the username, in e-mail address format, to authenticate.
 * @param string $pass
 *   string that is the password for the user specified.
 *
 * @return object
 *   Zend_Http_Client returns a client object.
 */
function droogle_get_client_login_http_client($user, $pass) {
  $service = Zend_Gdata_Docs::AUTH_SERVICE_NAME;
  $client = Zend_Gdata_ClientLogin::getHttpClient($user, $pass, $service);
  return $client;
}

/**
 * Prints google docs list.
 *
 * Prints google docs list output in an unordered list.
 *
 * @param object $feed
 *   An object with the google document list info, titles,
 *   document types, etc.
 * @param boolean $html
 *   Boolean deciding if to print a text list or html
 *   formatted list of google docs.
 *
 * @return string
 *   Returns google docs list as an html string
 */
function droogle_print_documents_feed($feed, $html) {
  try {
    $content = "";
    if ($html) {
      $content = "<ul>\n";
    }

    // Iterate over the document entries in the feed and display each document's
    // title.
    foreach ($feed->entries as $entry) {

      if ($html) {
        // Find the URL of the HTML view of the document.
        $alternate_link = '';
        foreach ($entry->link as $link) {
          if ($link->getRel() === 'alternate') {
            $alternate_link = $link->getHref();
          }
        }
        // Make the title link to the document on docs.google.com.
        $content .= "<li><a href=\"$alternate_link\">\n";
      }

      $content .= "$entry->title\n";

      if ($html) {
        $content .= "</a></li>\n";
      }
    }
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }
  return $content;
}

/**
 * API wrapper for google doc upload.
 *
 * API wrapper to upload document to a google docs account.
 *
 * @param string $user
 *   string with the google user name.
 * @param string $password
 *   string with the google password for the account.
 * @param object $docs
 *   an object with the google docs client info already authenticated.
 * @param boolean $html
 *   boolean and if TRUE then function will return html rather than text.
 * @param string $original_file_name
 *   string with the files name that will be uploaded.
 * @param string $temporary_file_location
 *   string with where the file is stored on the local file system.
 *
 * @return string
 *   a string is returned with either an error message or the message
 *   Success ... return is just used for debugging.
 */
function droogle_upload_document($user, $password, $docs, $html, $original_file_name, $temporary_file_location) {
  try{
    $file_to_upload = $original_file_name;
    if ($temporary_file_location) {
      $file_to_upload = $temporary_file_location;
    }

    // Upload the file and convert it into a Google Document. The original
    // file name is used as the title of the document and the MIME type
    // is determined based on the extension on the original file name.
    $file_name_parts = explode('.', $temporary_file_location);
    $file_extension = end($file_name_parts);
    $mime_type = Zend_Gdata_Docs::lookupMimeType($file_extension);
    $new_document_entry = $docs->uploadFile($file_to_upload, $original_file_name, $mime_type, Zend_Gdata_Docs::DOCUMENTS_LIST_FEED_URI);

    if ($html) {
      // Find the URL of the HTML view of this document.
      $alternate_link = '';
      foreach ($new_document_entry->link as $link) {
        if ($link->getRel() === 'alternate') {
          $alternate_link = $link->getHref();
        }
      }
      // Make the title link to the document on docs.google.com.
    }
    // Usage: echo $new_document_entry->title . "\n";
    $content = "Success";
    return $content;
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }
}

/**
 * Add permissons for google docs.
 *
 * Adds a permission to a google docs file.
 * This api function is not currently used by the module but shows usage
 * these are notes for my future use as well.
 *
 * @param string $document_id
 *   string with the google document id.
 * @param string $user
 *   the user (string) to add permissions for.
 */
function droogle_add_permission($document_id, $user) {
  // To share a collection, provide a collection resource ID instead
  // of a document ID.
  // http://code.google.com/apis/documents/docs/3.0/
  // developers_guide_protocol.html#ACLSharingCollections
  // Example user might be:
  // $user = 'drupal_development@babson.edu';
  // Example document_id might be:
  // $document_id = '1mKjGghPEU2hfcoU82gPPXT2G0wkBPrIQtPch01-X3BA';
  $client_acl = droogle_get_client_login_http_client('username@domain.edu', 'password');
  $method = 'POST';
  $headers['GData-Version'] = '3.0';
  $contenttype = 'application/atom+xml';

  // This url can be hardcoded or, as in this example,
  // Or can be dynamically run via a var $docId and $user for sharing
  // $acl_url = 'http://docs.google.com/feeds/default/private/full
  // /spreadsheet%3A' . $docId . '/acl';
  // $document_id = '1-qYaniUyBYDPNMIos2Rs60RPruYKv17qzRG8mjR-V88';
  // $document_id = '1mKjGghPEU2hfcoU82gPPXT2G0wkBPrIQtPch01-X3BA';
  // get this id by clicking on a url on the droogle page and
  // grab the document id.
  // API guide:  http://code.google.com/apis/documents/docs.
  // /3.0/developers_guide_protocol.html to share a
  // Collection http://code.google.com/apis/documents/docs/3.0
  // /developers_guide_protocol.html#ACLSharingCollections
  // by default user will be emailed they have been
  // granted access ... to suppress the email
  // use POST /feeds/default/private/full/document:12345
  // /acl?send-notification-emails=false
  $acl_url = "https://docs.google.com/feeds/default/private/full/" . $document_id . "/acl";

  $acl_entry = '<entry xmlns="http://www.w3.org/2005/Atom" xmlns:gAcl="http://schemas.google.com/acl/2007">';
  $acl_entry .= "<category scheme='http://schemas.google.com/g/2005#kind'
     term='http://schemas.google.com/acl/2007#accessRule'/>";
  $acl_entry .= "<gAcl:role value='writer'/>";

  $acl_entry .= "<gAcl:scope type='user' value='drupal_development@babson.edu'/>";
  $acl_entry .= "</entry>";

  $gdata_acl = new Zend_Gdata($client_acl);

  try {
    $gdata_acl->performHttpRequest($method, $acl_url, $headers, $acl_entry, $contenttype);
  } catch (Zend_Gdata_App_Exception $ex) {
    // Report the exception to the user.
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $ex->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $ex->getMessage()));
      return t('Error: %the_error', array('%message' => $ex->getMessage()));
    }
  }
}

/**
 * API for creating a google docs collection.
 *
 * Creates a google docs collection.
 *
 * @param string $folder_name
 *   A string with the name of the new folder.
 *
 * @return string
 *   A string is returned showing if successful.
 */
function droogle_create_collection($folder_name = "test_folder") {
  $client_acl = droogle_get_client_login_http_client('username@domain.edu', 'password');
  // $user = 'drupal_development@babson.edu';
  $method = 'POST';
  $headers['GData-Version'] = '3.0';
  $contenttype = 'application/atom+xml';

   // This url can be hardcoded or, as in this example,
   // can be dynamically run via a var $docId and $user for sharing
   // $acl_url = 'http://docs.google.com/feeds/default/private
   // /full/spreadsheet%3A' . $docId . '/acl';
   // $document_id = '1-qYaniUyBYDPNMIos2Rs60RPruYKv17qzRG8mjR-V88';
   // $document_id = '1mKjGghPEU2hfcoU82gPPXT2G0wkBPrIQtPch01-X3BA';
   // get this id by clicking on a url on the droogle page and grab
   // the document id.
   // API guide:  http://code.google.com/apis/documents/docs
   // /3.0/developers_guide_protocol.html
   // to share a collection http://code.google.com/apis/documents/docs/3.0
   // /developers_guide_protocol.html#ACLSharingCollections
   // by default user will be emailed they have been granted access
   // ... to suppress the email
   // use POST /feeds/default/private/full/document:12345
   // /acl?send-notification-emails=false
  $url = "https://docs.google.com/feeds/default/private/full";

  $entry = '<entry xmlns="http://www.w3.org/2005/Atom" xmlns:gAcl="http://schemas.google.com/acl/2007">';
  $entry .= "<category scheme='http://schemas.google.com/g/2005#kind' term='http://schemas.google.com/docs/2007#folder'/>";
  $entry .= "<title type='text'>" . $folder_name . "</title>";

  $entry .= "</entry>";

  $gdata_acl = new Zend_Gdata($client_acl);

  try {
    $gdata_acl->performHttpRequest($method, $url, $headers, $entry, $contenttype);
  } catch (Zend_Gdata_App_Exception $ex) {
    // Report the exception to the user.
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $ex->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $ex->getMessage()));
      return t('Error: %the_error', array('%message' => $ex->getMessage()));
    }
  }
  return 'folder was successfully created';
}

/**
 * Adds a file to a collection.
 *
 * Adds a file already in the users google docs
 * account to a google collection (folder).
 *
 * @param string $collection_id
 *   string with the google collection id.
 * @param string $document_id
 *   string with the google document id.
 *
 * @return string
 *   returns a string with text to indicate if successful.
 */
function droogle_add_to_collection($collection_id, $document_id) {
  $client_acl = droogle_get_client_login_http_client('username@domain.edu', 'password');
  $method = 'POST';
  $headers['GData-Version'] = '3.0';
  $contenttype = 'application/atom+xml';
  // Example $collection_id might be
  // '0B-a-StXYm5kcZDE0YmExOGEtNDg3MS00M2UwLWE4YWItYTEzZjAxNjcyYjE0'.
  // Example $document_id might be
  // '1mKjGghPEU2hfcoU82gPPXT2G0wkBPrIQtPch01-X3BA'.
  // This url can be hardcoded or, as in this example,
  // can be dynamically run via a var $docId and $user for sharing
  // $acl_url = 'http://docs.google.com/feeds/default/private
  // /full/spreadsheet%3A' . $docId . '/acl';
  // $document_id = '1-qYaniUyBYDPNMIos2Rs60RPruYKv17qzRG8mjR-V88';
  // $document_id = '1mKjGghPEU2hfcoU82gPPXT2G0wkBPrIQtPch01-X3BA';
  // get this id by clicking on a url on the droogle page and grab
  // the document id
  // api guide:  http://code.google.com/apis/documents/docs
  // /3.0/developers_guide_protocol.html
  // to share a collection http://code.google.com/apis/documents
  // /docs/3.0/developers_guide_protocol.html#ACLSharingCollections
  // by default user will be emailed they have been granted access
  // ... to suppress the email
  // use POST /feeds/default/private/full/document:12345
  // /acl?send-notification-emails=false
  $url = "https://docs.google.com//feeds/default/private/full/folder%3A" . $collection_id . "/contents";

  $entry = '<entry xmlns="http://www.w3.org/2005/Atom" xmlns:gAcl="http://schemas.google.com/acl/2007">';
  $entry .= "<category scheme='http://schemas.google.com/g/2005#kind' term='http://schemas.google.com/docs/2007#folder'/>";
  $entry .= "<id>https://docs.google.com/feeds/default/private/full/" . $document_id . "</id>";

  $entry .= "</entry>";

  $gdata_acl = new Zend_Gdata($client_acl);

  try {
    $gdata_acl->performHttpRequest($method, $url, $headers, $entry, $contenttype);
  } catch (Zend_Gdata_App_Exception $ex) {
    // Report the exception to the user.
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $ex->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $ex->getMessage()));
      return t('Error: %the_error', array('%message' => $ex->getMessage()));
    }
  }
  // Returning 0 indicates success.
  return 'document was successfully added to the collection';
}

/**
 * Gets a list of google docs folders.
 *
 * Prints out an html list of google docs which
 * goes through a drupal theme function.
 *
 * @param string $user
 *   string with the google username.
 * @param string $password
 *   string with the google password.
 * @param string $domain
 *   string with the domain of the google account.
 * @param string $collection_id
 *   string with the google collection_id, just this
 *   collection will be printed out.
 *
 * @return string
 *   returns html string in the $content variable.
 */
function droogle_get_folders($user = NULL, $password = NULL, $domain = NULL, $collection_id = NULL) {
  // Construct an HTTP POST request.
  // Example collection_id might be:
  // $collection_id =
  // '0B4mZRjHDl6MvZTA3NzBiMDctOTQ1NS00MGM5LWE2ZTUtNWYwZWYzMmJhMWI3'.
  $clientlogin_url = "https://www.google.com/accounts/ClientLogin";

  $clientlogin_post = array(
    "accountType" => "HOSTED_OR_GOOGLE",
    "Email" => $user,
    "Passwd" => $password,
    "service" => "writely",
    "source" => "Droogle",
  );
  // Initialize the curl object.
  $curl = curl_init($clientlogin_url);
  // Set some options (some for SHTTP).
  curl_setopt($curl, CURLOPT_POST, TRUE);
  curl_setopt($curl, CURLOPT_POSTFIELDS, $clientlogin_post);
  curl_setopt($curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
  curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  // Execute.
  $response = curl_exec($curl);
  // Uncomment below line to diagnose login problems.
  // drupal_set_message('<pre>' . print_r($response, TRUE) . '</pre>');
  // Get the Auth string and save it.
  preg_match("/Auth=([a-z0-9_\-]+)/i", $response, $matches);
  $auth = $matches[1];
  // Echo "The auth string is: " . $auth;
  // Include the Auth string in the headers
  // together with the API version being used.
  $headers = array(
    "Authorization: GoogleLogin auth=" . $auth,
    "GData-Version: 3.0",
  );

  // Make the request.
  $url = "https://docs.google.com/feeds/default/private/full/-/folder";
  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
  curl_setopt($curl, CURLOPT_POST, FALSE);
  $response = curl_exec($curl);
  curl_close($curl);
  // Parse the response.
  $response = simplexml_load_string($response);
  // Output data.
  $content = "";
  $content .= theme('droogle_print_folders', $response);
  return $content;
}

/**
 * Prints out an html list of google collections for a given user.
 *
 * Prints out an html list of google docs which
 * goes through a drupal theme function.
 *
 * @param string $user
 *   string with the google username.
 * @param string $password
 *   string with the google password.
 * @param string $domain
 *   string with the domain of the google account.
 * @param string $collection_id
 *   string with the google collection_id, just this
 *   collection will be printed out.
 *
 * @return string
 *   returns html string in the $content variable.
 */
function droogle_print_collections($user = NULL, $password = NULL, $domain = NULL, $collection_id = NULL) {
  // Construct an HTTP POST request.
  // Example collection_id might be:
  // $collection_id =
  // '0B4mZRjHDl6MvZTA3NzBiMDctOTQ1NS00MGM5LWE2ZTUtNWYwZWYzMmJhMWI3'.
  $clientlogin_url = "https://www.google.com/accounts/ClientLogin";

  $clientlogin_post = array(
    "accountType" => "HOSTED_OR_GOOGLE",
    "Email" => $user,
    "Passwd" => $password,
    "service" => "writely",
    "source" => "Droogle",
  );
  // Initialize the curl object.
  $curl = curl_init($clientlogin_url);
  // Set some options (some for SHTTP).
  curl_setopt($curl, CURLOPT_POST, TRUE);
  curl_setopt($curl, CURLOPT_POSTFIELDS, $clientlogin_post);
  curl_setopt($curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
  curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  // Execute.
  $response = curl_exec($curl);
  // Get the Auth string and save it.
  preg_match("/Auth=([a-z0-9_\-]+)/i", $response, $matches);
  $auth = $matches[1];
  // Echo "The auth string is: " . $auth;
  // Include the Auth string in the headers
  // together with the API version being used.
  $headers = array(
    "Authorization: GoogleLogin auth=" . $auth,
    "GData-Version: 3.0",
  );

  // Make the request.
  // Adding /folder%3Aroot/contents/-/folder" to the end of the url below.
  // makes it so it will only fetch collection names (folder names).
  if ($collection_id == NULL) {
    $url = "https://docs.google.com/feeds/default/private/full";
  }
  elseif ($collection_id == 'root') {
    // Below url shows both all folders and documents from the My Drive folder
    // (not the Shared with me folder).
    $url = "https://docs.google.com/feeds/default/private/full/-/root?showfolders=true";
  }
  elseif ($collection_id = 'mine') {
    //  Below url shows both all folders and documents from the Shared with me
    //  folder.
    $url = "https://docs.google.com/feeds/default/private/full/-/-mine?showfolders=true";
  }
  elseif ($collection_id = 'folders') {
    $url = "https://docs.google.com/feeds/default/private/full/-/folder";
  }
  else {
    $url = "https://docs.google.com/feeds/default/private/full/folder%3A" . $collection_id . "/contents?showfolders=false";
  }
  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
  curl_setopt($curl, CURLOPT_POST, FALSE);
  $response = curl_exec($curl);
  curl_close($curl);
  // Parse the response.
  $response = simplexml_load_string($response);
  return $response;
}


/**
 * API to retrieve google user info.
 *
 * Retrieves information about a user from the google api.
 *
 * @param string $username
 *   a string with the username to grab information about.
 *
 * @return array
 *   returns an array of user information.
 */
function droogle_retrieve_user($username) {
  $client = Zend_Gdata_ClientLogin::getHttpClient('username@domain.edu', 'password', Zend_Gdata_Gapps::AUTH_SERVICE_NAME);
  $domain = "babson.edu";
  try {
    $gdata = new Zend_Gdata_Gapps($client, $domain);
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }

  $user = $gdata->retrieveUser($username);
  try{
    if (!$user) {
      throw new Exception("ERROR: The user object has no data");
    }
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }
  $user_array = array();
  $user_array['username'] = $user->login->userName;
  $user_array['givenname'] = $user->name->givenName;
  $user_array['familyname'] = $user->name->familyName;
  $user_array['suspended'] = $user->login->suspended ? 'Yes' : 'No';
  $user_array['admin'] = $user->login->admin ? 'Yes' : 'No';
  $user_array['changePasswordAtNextLogin'] = $user->login->changePasswordAtNextLogin ? 'Yes' : 'No';
  $user_array['agreedToTerms'] = $user->login->agreedToTerms ? 'Yes' : 'No';

  // Usage example: echo 'Username: ' . $user->login->userName . "\n";
  // echo 'Given Name: ' . $user->name->givenName . "\n";
  // echo 'Family Name: ' . $user->name->familyName . "\n";
  // echo 'Suspended: ' . ($user->login->suspended ? 'Yes' : 'No') . "\n";
  // echo 'Admin: ' . ($user->login->admin ? 'Yes' : 'No') . "\n";
  // echo 'Must Change Password: ' . ($user->login
  // ->changePasswordAtNextLogin ? 'Yes' : 'No') . "\n";
  // echo 'Has Agreed To Terms: ' . ($user->login->agreedToTerms
  // ? 'Yes' : 'No') . "\n";
  return $user_array;
}

/**
 * API call to change a google users password.
 *
 * A wrapper to invoke the google api to change a users password.
 *
 * @param string $username
 *   string with the username whos password you want to change.
 * @param string $newuserpassword
 *   string with the new password that will be set.
 *
 * @return boolean
 *   returns TRUE upon success.
 */
function droogle_change_password($username, $newuserpassword) {
  $client = Zend_Gdata_ClientLogin::getHttpClient('username@domain.edu', 'password', Zend_Gdata_Gapps::AUTH_SERVICE_NAME);
  $domain = "babson.edu";
  try {
    $gdata = new Zend_Gdata_Gapps($client, $domain);
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }

  // Now change the user's password.
  $update_user = $gdata->retrieveUser($username);
  try {
    if (!$update_user) {
      throw new Exception("ERROR: The update_user object has no data");
    }
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }
  // Usage: echo 'Username: ' . $update_user->login->userName . "\n";
  // echo 'Given Name: ' . $update_user->name->givenName . "\n";
  // echo 'Family Name: ' . $update_user->name->familyName . "\n";
  // echo 'Suspended: ' . ($update_user->login->suspended ?
  // 'Yes' : 'No') . "\n";
  // echo 'Admin: ' . ($update_user->login->admin ? 'Yes' : 'No') . "\n";
  // echo 'Must Change Password: ' . ($update_user->login
  // ->changePasswordAtNextLogin ? 'Yes' : 'No') . "\n";
  // echo 'Has Agreed To Terms: ' . ($update_user->login->
  // agreedToTerms ? 'Yes' : 'No') . "\n";
  $update_user->login->password = $newuserpassword;
  $update_user = $update_user->save();

  return TRUE;
}

/**
 * API call to create a new google user.
 *
 * Wrapper to create a new google user via the google api.
 *
 * @param string $username
 *   a string with the username to be created.
 * @param string $givenname
 *   a string with the users first name.
 * @param string $familyname
 *   a string with the users last name.
 * @param string $password
 *   a string with the new users password.
 *
 * @return boolean
 *   returns true if a user is successfully created.
 */
function droogle_create_user($username, $givenname, $familyname, $password) {
  $client = Zend_Gdata_ClientLogin::getHttpClient('username@domain.edu', 'password', Zend_Gdata_Gapps::AUTH_SERVICE_NAME);
  $domain = "babson.edu";
  try {
    $gdata = new Zend_Gdata_Gapps($client, $domain);
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }

  // Now try creating a user.
  try {
    $gdata->createUser($username, $givenname, $familyname, $password);
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }

  return TRUE;

}

/**
 * A wrapper to create a google user via their api.
 *
 * @param string $username
 *   a string with the username to be deleted from google.
 *
 * @return boolean
 *   returns true upon successful deletion of the user.
 */
function droogle_delete_user($username) {
  $client = Zend_Gdata_ClientLogin::getHttpClient('username@domain.edu', 'password', Zend_Gdata_Gapps::AUTH_SERVICE_NAME);
  $domain = "babson.edu";
  try {
    $gdata = new Zend_Gdata_Gapps($client, $domain);
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }

  // Now try creating a user.
  $user = $gdata->retrieveUser($username);
  try {
    if (!$user) {
      throw new Exception("ERROR: The update_user object has no data");
    }
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }
  $user->delete();


  return TRUE;

}

/**
 * Retrieve all users from google for a given domain.
 *
 * Retrieves all users from a given google domain.
 *
 * @todo:  params are hardcoded currently.
 */
function droogle_retrieve_all_users() {
  $client = Zend_Gdata_ClientLogin::getHttpClient('username@domain.edu', 'password', Zend_Gdata_Gapps::AUTH_SERVICE_NAME);
  $domain = "babson.edu";
  try {
    $gdata = new Zend_Gdata_Gapps($client, $domain);
  } catch (Exception $e) {
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $e->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $e->getMessage()));
      return t('Error: %the_error', array('%message' => $e->getMessage()));
    }
  }

  $feed = $gdata->retrieveAllUsers();
  $count = 0;
  foreach ($feed as $user) {
    $count++;
    echo "  * " . $user->login->username . ' (' . $user->name->givenName .
        ' ' . $user->name->familyName . ")\n";
  }
  echo 'total number of users: ' . $count;
}

/**
 * Get a collection id from google.
 *
 * Get the collection id for a collection (google folder).
 *
 * @param string $user
 *   a string with the google username.
 * @param string $password
 *   a string with the google password.
 * @param string $desired_collection_title
 *   a string with the english name of the folder which youll get an id for.
 *
 * @return string
 *   returns a string with the collection_id.
 */
function droogle_get_a_collection_id($user, $password, $desired_collection_title) {
  // feeds/default/private/full/-/folder
  // Construct an HTTP POST request.
  $client_acl = droogle_get_client_login_http_client($user, $password);
  $method = 'GET';
  $headers['GData-Version'] = '3.0';
  $contenttype = 'application/atom+xml';

  // This url can be hardcoded or, as in this example,
  // can be dynamically run via a var $docId and $user for sharing
  // $acl_url = 'http://docs.google.com/feeds/default/private
  // /full/spreadsheet%3A' . $docId . '/acl';
  // $document_id = '1-qYaniUyBYDPNMIos2Rs60RPruYKv17qzRG8mjR-V88';
  // $document_id = '1mKjGghPEU2hfcoU82gPPXT2G0wkBPrIQtPch01-X3BA';
  // get this id by clicking on a url on the droogle page and
  // grab the document id.
  // API guide:  http://code.google.com/apis/documents/docs.
  // /3.0/developers_guide_protocol.html
  // to share a collection http://code.google.com/apis/documents
  // /docs/3.0/developers_guide_protocol.html#ACLSharingCollections
  // by default user will be emailed they have been granted access
  // ... to suppress the email
  // use POST /feeds/default/private/full/document:12345
  // /acl?send-notification-emails=false
  $url = "https://docs.google.com/feeds/default/private/full/-/folder";
  $entry = NULL;
  $gdata_acl = new Zend_Gdata($client_acl);

  try {
    $response = $gdata_acl->performHttpRequest($method, $url, $headers, $entry, $contenttype);
  } catch (Zend_Gdata_App_Exception $ex) {
    // Report the exception to the user.
    if (php_sapi_name() == 'cli') {
      return 'Error: ' . $ex->getMessage();
    }
    else {
      watchdog("DROOGLE", "Error: @the_error", array('@the_error' => $ex->getMessage()));
      return t('Error: %the_error', array('%message' => $ex->getMessage()));
    }
  }
  // http://www.welmers.net/~bastiaan/ZendFramework-1.5.3
  // /documentation/manual/core/en/zend.http.response.html
  // This url shows how to parse the results.
  $body = $response->getBody();
  $xml = simplexml_load_string($body);
  // Usage: $docurl = droogle_xml_attribute($xml->entry->content,'src');
  // preg_match("/folder%3A(.*)\/contents/i", $docurl, $matches);
  // $collection_id = $matches[1];
  $collection_id = "";
  $collection_titles = "";
  $result_array = array();
  // print_r($xml->entry);
  foreach ($xml->entry as $object) {
    if ($object->title != $desired_collection_title) {
      continue;
    }
    $collection_title = $object->title;
    $docurl = droogle_xml_attribute($object->content, 'src');
    preg_match("/folder%3A(.*)\/contents/i", $docurl, $matches);
    $collection_id = $matches[1];
    // Usage:  $result_array[$collection_title] = $collection_id;
    // $collection_titles .= $object->title.',';
    // $collection_titles .= droogle_xml_attribute($object->content,'src');
  }
    // Usage example:  $collection_titles .= ','.$collection_id;
    return $collection_id;
}

/**
 * Helper function dealing with attribute.
 *
 * Helper function getting an attribute.
 *
 * @param object $object
 *   droogle_get_a_collection_id function passes
 *   an object to this helper function
 * @param string $attribute
 *   attribute is retrieved from object passed
 *   to this function by droogle_get_a_collection_id
 *
 * @return string
 *   returns a string with the attribute
 */
function droogle_xml_attribute($object, $attribute) {
  if (isset($object[$attribute])) {
    return (string) $object[$attribute];
  }
}

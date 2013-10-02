<?php
/**
 * @file
 * Contains functions only needed for drush integration.
 */

/**
 * Implementation of hook_drush_command().
 */
function groundwork_drush_command() {
  $items = array();

  $items['groundwork'] = array(
    'description' => 'Create a theme using the Groundwork Theme Framework.',
    'arguments' => array(
      'name'         => 'A name for your theme.',
      'machine_name' => '[optional] A machine-readable name for your theme.',
    ),
    'options' => array(
      'name'                 => 'A name for your theme.',
      'machine-name'         => '[a-z, 0-9] A machine-readable name for your theme.',
      'description'          => 'A description of your theme.',
    ),
    'examples' => array(
      'drush groundwork \'Philippine Sea\'' => 'Create a custom theme called Philippine Sea, using the default options.',
      'drush groundwork \'Philippine Sea\' philsea' => 'Create a custom theme called Philippine Sea with a specific machine name philsea.',
      'drush groundwork \'Philippine Sea\' philsea --description=\'My deep blue green custom theme.\'' => 'Create a custom theme called Philippine Sea, with a specific machine name philsea and a description.',
    ),
  );

  return $items;
}

/**
 * Create a Groundwork sub-theme using the CustomWork kit.
 */
function drush_groundwork($name = NULL, $machine_name = NULL) {
  // Determine the theme name.
  if (!isset($name)) {
    $name = drush_get_option('name');
  }

  // Determine the machine name.
  if (!isset($machine_name)) {
    $machine_name = drush_get_option('machine-name');
  }
  if (!$machine_name) {
    $machine_name = $name;
  }
  $machine_name = str_replace(' ', '_', strtolower($machine_name));
  $search = array(
    '/[^a-z0-9_]/', // Remove characters not valid in function names.
    '/^[^a-z]+/',   // Functions must begin with an alpha character.
  );
  $machine_name = preg_replace($search, '', $machine_name);

  // Determine the path to the new subtheme by finding the path to Groundwork.
  $groundwork_path = 'sites/all/themes/groundwork';
  $subtheme_path = explode('/', $groundwork_path);
  array_pop($subtheme_path);
  $subtheme_path = implode('/', $subtheme_path) . '/' . str_replace('_', '-', $machine_name);

  // Make a fresh copy of the original CustomWork.
  drush_op('groundwork_copy', $groundwork_path . '/CustomWork', $subtheme_path);

  // Rename the .info file.
  $subtheme_info_file = $subtheme_path . '/' . $machine_name . '.info';
  drush_op('rename', $subtheme_path . '/CustomWork.info.txt', $subtheme_info_file);

  // Alter the contents of the .info file based on the command options.
  $info_alterations = array(
    '= CustomWork for Groundwork' => '= ' . $name,
  );
  if ($description = drush_get_option('description')) {
    $info_alterations['Read the <a href="http://groundwork.noceda.no/handbook">online handbook</a> or the included README.txt on how to create a subtheme of Groundwork.'] = $description;
  }
  drush_op('groundwork_file_str_replace', $subtheme_info_file, array_keys($info_alterations), $info_alterations);

  // Replace all occurrences of 'CustomWork' with the machine name of our sub theme.
  drush_op('groundwork_file_str_replace', $subtheme_path . '/theme-settings.php', 'CustomWork', $machine_name);
  drush_op('groundwork_file_str_replace', $subtheme_path . '/template.php', 'CustomWork', $machine_name);

  // Notify user of the newly created theme.
  drush_print(dt('CustomWork for "!name" created in: !path', array(
    '!name' => $name,
    '!path' => $subtheme_path,
  )));
}

/**
 * Copy a directory recursively.
 */
function groundwork_copy($source_dir, $target_dir, $ignore = '/^(\.(\.)?|CVS|\.svn|\.git|\.DS_Store)$/') {
  if (!is_dir($source_dir)) {
    drush_die(dt('The directory "!directory" was not found.', array('!directory' => $source_dir)));
  }
  $dir = opendir($source_dir);
  @mkdir($target_dir);
  while($file = readdir($dir)) {
    if (!preg_match($ignore, $file)) {
      if (is_dir($source_dir . '/' . $file)) {
        groundwork_copy($source_dir . '/' . $file, $target_dir . '/' . $file, $ignore);
      }
      else {
        copy($source_dir . '/' . $file, $target_dir . '/' . $file);
      }
    }
  }
  closedir($dir);
}

/**
 * Replace strings in a file.
 */
function groundwork_file_str_replace($file_path, $find, $replace) {
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}

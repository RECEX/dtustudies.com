<?php

/**
 * @file
 * Skinr settings for Groundwork.
 *
 * Declares 2 new Skinr groups and numerous Skinr styles.
 */

/* Implements hook_skinr_group_info(). */
function groundwork_skinr_group_info() {
  $groups['grid_system'] = array(
    'title' => t('24-Column Grid System'),
    'description' => t('<p>Blocks in the top bar, navigation bar, billboard, highlighted, appendix, supplement and footer regions can have a maximum of 24 columns, the header region with a maximum of 12 columns, sidebar first with a maximum of 8 columns, sidebar second with 4 columns. The blocks in the aside region will always have 5 columns with no prefix and/or suffix. Columns in the main content region vary depending on the visibility of the sidebars.</p> <p><strong>Important!</strong> Do not assign a number of columns that are more than the total number of columns (width + prefix + suffix) the region can hold.</p>'),
    'weight' => '0'
  );
  $groups['presentation'] = array(
    'title' => t('Presentation'),
    'description' => t('Presentational styles'),
    'weight' => '0'
  );
  return $groups;
}

/* Implements hook_skinr_skin_info(). */
function groundwork_skinr_skin_info() {
  // Provides different block widths options.
  $skins['groundwork_content_width'] = array(
    'title' => t('Block Width'),
    'description' => t('Assigning a larger number of columns than what the region can hold will inherit the width of the maximum number of columns allowed.'),
    'type' => 'select',
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 1,
      'negosyante' => 1,
      'nocedark' => 1,
      'mayumi' => 1,
      'kalikasan' => 1,
      'nyebe' => 1,
      'hatinggabi' => 1,
    ),
    'theme hooks' => array('block'),
    'group' => 'grid_system',
    'weight' => '1',
    'options' => array(
      'noceda_block_width_1' => array('title' => t('1 column'), 'class' => array('grid-1')),
      'noceda_block_width_2' => array('title' => t('2 columns'), 'class' => array('grid-2')),
      'noceda_block_width_3' => array('title' => t('3 columns'), 'class' => array('grid-3')),
      'noceda_block_width_4' => array('title' => t('4 columns'), 'class' => array('grid-4')),
      'noceda_block_width_5' => array('title' => t('5 columns'), 'class' => array('grid-5')),
      'noceda_block_width_6' => array('title' => t('6 columns'), 'class' => array('grid-6')),
      'noceda_block_width_7' => array('title' => t('7 columns'), 'class' => array('grid-7')),
      'noceda_block_width_8' => array('title' => t('8 columns'), 'class' => array('grid-8')),
      'noceda_block_width_9' => array('title' => t('9 columns'), 'class' => array('grid-9')),
      'noceda_block_width_10' => array('title' => t('10 columns'), 'class' => array('grid-10')),
      'noceda_block_width_11' => array('title' => t('11 columns'), 'class' => array('grid-11')),
      'noceda_block_width_12' => array('title' => t('12 columns'), 'class' => array('grid-12')),
      'noceda_block_width_13' => array('title' => t('13 columns'), 'class' => array('grid-13')),
      'noceda_block_width_14' => array('title' => t('14 columns'), 'class' => array('grid-14')),
      'noceda_block_width_15' => array('title' => t('15 columns'), 'class' => array('grid-15')),
      'noceda_block_width_16' => array('title' => t('16 columns'), 'class' => array('grid-16')),
      'noceda_block_width_17' => array('title' => t('17 columns'), 'class' => array('grid-17')),
      'noceda_block_width_18' => array('title' => t('18 columns'), 'class' => array('grid-18')),
      'noceda_block_width_19' => array('title' => t('19 columns'), 'class' => array('grid-19')),
      'noceda_block_width_20' => array('title' => t('20 columns'), 'class' => array('grid-20')),
      'noceda_block_width_21' => array('title' => t('21 columns'), 'class' => array('grid-21')),
      'noceda_block_width_22' => array('title' => t('22 columns'), 'class' => array('grid-22')),
      'noceda_block_width_23' => array('title' => t('23 columns'), 'class' => array('grid-23')),
      'noceda_block_width_24' => array('title' => t('24 columns'), 'class' => array('grid-24')),
    ),
  );
  // Implements the 960.gs alpha and omega. Provides options to remove block side margins.
  $skins['groundwork_grid_gutters'] = array(
    'title' => t('Remove gutters'),
    'description' => t('On the same region, left gutters of the farthest left blocks and right gutters of the farthest right blocks must be removed. (You still need to remove the gutters if you assigned a width to a single block).'),
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 1,
      'negosyante' => 1,
      'nocedark' => 1,
      'mayumi' => 1,
      'kalikasan' => 1,
      'nyebe' => 1,
      'hatinggabi' => 1,
    ),
    'theme hooks' => array('block'),
    'group' => 'grid_system',
    'weight' => '2',
    'options' => array(
      'noceda_gutter_1' => array(
        'title' => t('Remove left gutters. Check if this block has no other blocks on its left in the same region.'),
        'class' => array('alpha'),
      ),
      'noceda_gutter_2' => array(
        'title' => t('Remove right gutter. Check if this block has no other blocks on its right on the same region.'),
        'class' => array('omega'),
      ),
    ),
  );
  // Implements the 960.gs prefix
  $skins['groundwork_prefix'] = array(
    'title' => t('Prefix'),
    'description' => t('Allows you to add in blank columns before the block. The number specifies how many blank columns you want. WARNING: Choosing a prefix wider than the region\'s width will break the layout.'),
    'type' => 'select',
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 1,
      'negosyante' => 1,
      'nocedark' => 1,
      'mayumi' => 1,
      'kalikasan' => 1,
      'nyebe' => 1,
      'hatinggabi' => 1,
    ),
    'theme hooks' => array('block'),
    'group' => 'grid_system',
    'weight' => '3',
    'options' => array(
      'noceda_block_prefix_1' => array('title' => t('Prefix block with 1 column'), 'class' => array('prefix-1')),
      'noceda_block_prefix_2' => array('title' => t('Prefix block with 2 columns'), 'class' => array('prefix-2')),
      'noceda_block_prefix_3' => array('title' => t('Prefix block with 3 columns'), 'class' => array('prefix-3')),
      'noceda_block_prefix_4' => array('title' => t('Prefix block with 4 columns'), 'class' => array('prefix-4')),
      'noceda_block_prefix_5' => array('title' => t('Prefix block with 5 columns'), 'class' => array('prefix-5')),
      'noceda_block_prefix_6' => array('title' => t('Prefix block with 6 columns'), 'class' => array('prefix-6')),
      'noceda_block_prefix_7' => array('title' => t('Prefix block with 7 columns'), 'class' => array('prefix-7')),
      'noceda_block_prefix_8' => array('title' => t('Prefix block with 8 columns'), 'class' => array('prefix-8')),
      'noceda_block_prefix_9' => array('title' => t('Prefix block with 9 columns'), 'class' => array('prefix-9')),
      'noceda_block_prefix_10' => array('title' => t('Prefix block with 10 columns'), 'class' => array('prefix-10')),
      'noceda_block_prefix_11' => array('title' => t('Prefix block with 11 columns'), 'class' => array('prefix-11')),
      'noceda_block_prefix_12' => array('title' => t('Prefix block with 12 columns'), 'class' => array('prefix-12')),
      'noceda_block_prefix_13' => array('title' => t('Prefix block with 13 columns'), 'class' => array('prefix-13')),
      'noceda_block_prefix_14' => array('title' => t('Prefix block with 14 columns'), 'class' => array('prefix-14')),
      'noceda_block_prefix_15' => array('title' => t('Prefix block with 15 columns'), 'class' => array('prefix-15')),
      'noceda_block_prefix_16' => array('title' => t('Prefix block with 16 columns'), 'class' => array('prefix-16')),
      'noceda_block_prefix_17' => array('title' => t('Prefix block with 17 columns'), 'class' => array('prefix-17')),
      'noceda_block_prefix_18' => array('title' => t('Prefix block with 18 columns'), 'class' => array('prefix-18')),
      'noceda_block_prefix_19' => array('title' => t('Prefix block with 19 columns'), 'class' => array('prefix-19')),
      'noceda_block_prefix_20' => array('title' => t('Prefix block with 20 columns'), 'class' => array('prefix-20')),
      'noceda_block_prefix_21' => array('title' => t('Prefix block with 21 columns'), 'class' => array('prefix-21')),
      'noceda_block_prefix_22' => array('title' => t('Prefix block with 22 columns'), 'class' => array('prefix-22')),
      'noceda_block_prefix_23' => array('title' => t('Prefix block with 23 columns'), 'class' => array('prefix-23')),
    ),
  );
  // Implements the 960.gs suffix
  $skins['groundwork_suffix'] = array(
    'title' => t('Suffix'),
    'description' => t('Allows you to add in blank columns after the block. The number specifies how many blank columns you want. WARNING: Choosing a suffix wider than the region\'s width will break the layout.'),
    'type' => 'select',
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 1,
      'negosyante' => 1,
      'nocedark' => 1,
      'mayumi' => 1,
      'kalikasan' => 1,
      'nyebe' => 1,
      'hatinggabi' => 1,
    ),
    'theme hooks' => array('block'),
    'group' => 'grid_system',
    'weight' => '4',
    'options' => array(
      'noceda_block_suffix_1' => array('title' => t('Suffix block with 1 column'), 'class' => array('suffix-1')),
      'noceda_block_suffix_2' => array('title' => t('Suffix block with 2 columns'), 'class' => array('suffix-2')),
      'noceda_block_suffix_3' => array('title' => t('Suffix block with 3 columns'), 'class' => array('suffix-3')),
      'noceda_block_suffix_4' => array('title' => t('Suffix block with 4 columns'), 'class' => array('suffix-4')),
      'noceda_block_suffix_5' => array('title' => t('Suffix block with 5 columns'), 'class' => array('suffix-5')),
      'noceda_block_suffix_6' => array('title' => t('Suffix block with 6 columns'), 'class' => array('suffix-6')),
      'noceda_block_suffix_7' => array('title' => t('Suffix block with 7 columns'), 'class' => array('suffix-7')),
      'noceda_block_suffix_8' => array('title' => t('Suffix block with 8 columns'), 'class' => array('suffix-8')),
      'noceda_block_suffix_9' => array('title' => t('Suffix block with 9 columns'), 'class' => array('suffix-9')),
      'noceda_block_suffix_10' => array('title' => t('Suffix block with 10 columns'), 'class' => array('suffix-10')),
      'noceda_block_suffix_11' => array('title' => t('Suffix block with 11 columns'), 'class' => array('suffix-11')),
      'noceda_block_suffix_12' => array('title' => t('Suffix block with 12 columns'), 'class' => array('suffix-12')),
      'noceda_block_suffix_13' => array('title' => t('Suffix block with 13 columns'), 'class' => array('suffix-13')),
      'noceda_block_suffix_14' => array('title' => t('Suffix block with 14 columns'), 'class' => array('suffix-14')),
      'noceda_block_suffix_15' => array('title' => t('Suffix block with 15 columns'), 'class' => array('suffix-15')),
      'noceda_block_suffix_16' => array('title' => t('Suffix block with 16 columns'), 'class' => array('suffix-16')),
      'noceda_block_suffix_17' => array('title' => t('Suffix block with 17 columns'), 'class' => array('suffix-17')),
      'noceda_block_suffix_18' => array('title' => t('Suffix block with 18 columns'), 'class' => array('suffix-18')),
      'noceda_block_suffix_19' => array('title' => t('Suffix block with 19 columns'), 'class' => array('suffix-19')),
      'noceda_block_suffix_20' => array('title' => t('Suffix block with 20 columns'), 'class' => array('suffix-20')),
      'noceda_block_suffix_21' => array('title' => t('Suffix block with 21 columns'), 'class' => array('suffix-21')),
      'noceda_block_suffix_22' => array('title' => t('Suffix block with 22 columns'), 'class' => array('suffix-22')),
      'noceda_block_suffix_23' => array('title' => t('Suffix block with 23 columns'), 'class' => array('suffix-23')),
    ),
  );
  // Implements the 960.gs push. Provides options to push the block.
  $skins['groundwork_push'] = array(
    'title' => t('Push'),
    'description' => t('Allows you to reposition the block horizontally by pushing it along the page.'),
    'type' => 'select',
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 1,
      'negosyante' => 1,
      'nocedark' => 1,
      'mayumi' => 1,
      'kalikasan' => 1,
      'nyebe' => 1,
      'hatinggabi' => 1,
    ),
    'theme hooks' => array('block'),
    'group' => 'grid_system',
    'weight' => '5',
    'options' => array(
      'noceda_block_push_1' => array('title' => t('Push block with 1 column'), 'class' => array('push-1')),
      'noceda_block_push_2' => array('title' => t('Push block with 2 columns'), 'class' => array('push-2')),
      'noceda_block_push_3' => array('title' => t('Push block with 3 columns'), 'class' => array('push-3')),
      'noceda_block_push_4' => array('title' => t('Push block with 4 columns'), 'class' => array('push-4')),
      'noceda_block_push_5' => array('title' => t('Push block with 5 columns'), 'class' => array('push-5')),
      'noceda_block_push_6' => array('title' => t('Push block with 6 columns'), 'class' => array('push-6')),
      'noceda_block_push_7' => array('title' => t('Push block with 7 columns'), 'class' => array('push-7')),
      'noceda_block_push_8' => array('title' => t('Push block with 8 columns'), 'class' => array('push-8')),
      'noceda_block_push_9' => array('title' => t('Push block with 9 columns'), 'class' => array('push-9')),
      'noceda_block_push_10' => array('title' => t('Push block with 10 columns'), 'class' => array('push-10')),
      'noceda_block_push_11' => array('title' => t('Push block with 11 columns'), 'class' => array('push-11')),
      'noceda_block_push_12' => array('title' => t('Push block with 12 columns'), 'class' => array('push-12')),
      'noceda_block_push_13' => array('title' => t('Push block with 13 columns'), 'class' => array('push-13')),
      'noceda_block_push_14' => array('title' => t('Push block with 14 columns'), 'class' => array('push-14')),
      'noceda_block_push_15' => array('title' => t('Push block with 15 columns'), 'class' => array('push-15')),
      'noceda_block_push_16' => array('title' => t('Push block with 16 columns'), 'class' => array('push-16')),
      'noceda_block_push_17' => array('title' => t('Push block with 17 columns'), 'class' => array('push-17')),
      'noceda_block_push_18' => array('title' => t('Push block with 18 columns'), 'class' => array('push-18')),
      'noceda_block_push_19' => array('title' => t('Push block with 19 columns'), 'class' => array('push-19')),
      'noceda_block_push_20' => array('title' => t('Push block with 20 columns'), 'class' => array('push-20')),
      'noceda_block_push_21' => array('title' => t('Push block with 21 columns'), 'class' => array('push-21')),
      'noceda_block_push_22' => array('title' => t('Push block with 22 columns'), 'class' => array('push-22')),
      'noceda_block_push_23' => array('title' => t('Push block with 23 columns'), 'class' => array('push-23')),
    ),
  );
  // Implements the 960.gs pull. Provides options to pull the block.
  $skins['groundwork_pull'] = array(
    'title' => t('Pull'),
    'description' => t('Allows you to reposition the block horizontally by pulling it along the page.'),
    'type' => 'select',
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 1,
      'negosyante' => 1,
      'nocedark' => 1,
      'mayumi' => 1,
      'kalikasan' => 1,
      'nyebe' => 1,
      'hatinggabi' => 1,
    ),
    'theme hooks' => array('block'),
    'group' => 'grid_system',
    'weight' => '6',
    'options' => array(
      'noceda_block_pull_1' => array('title' => t('Pull block with 1 column'), 'class' => array('pull-1')),
      'noceda_block_pull_2' => array('title' => t('Pull block with 2 columns'), 'class' => array('pull-2')),
      'noceda_block_pull_3' => array('title' => t('Pull block with 3 columns'), 'class' => array('pull-3')),
      'noceda_block_pull_4' => array('title' => t('Pull block with 4 columns'), 'class' => array('pull-4')),
      'noceda_block_pull_5' => array('title' => t('Pull block with 5 columns'), 'class' => array('pull-5')),
      'noceda_block_pull_6' => array('title' => t('Pull block with 6 columns'), 'class' => array('pull-6')),
      'noceda_block_pull_7' => array('title' => t('Pull block with 7 columns'), 'class' => array('pull-7')),
      'noceda_block_pull_8' => array('title' => t('Pull block with 8 columns'), 'class' => array('pull-8')),
      'noceda_block_pull_9' => array('title' => t('Pull block with 9 columns'), 'class' => array('pull-9')),
      'noceda_block_pull_10' => array('title' => t('Pull block with 10 columns'), 'class' => array('pull-10')),
      'noceda_block_pull_11' => array('title' => t('Pull block with 11 columns'), 'class' => array('pull-11')),
      'noceda_block_pull_12' => array('title' => t('Pull block with 12 columns'), 'class' => array('pull-12')),
      'noceda_block_pull_13' => array('title' => t('Pull block with 13 columns'), 'class' => array('pull-13')),
      'noceda_block_pull_14' => array('title' => t('Pull block with 14 columns'), 'class' => array('pull-14')),
      'noceda_block_pull_15' => array('title' => t('Pull block with 15 columns'), 'class' => array('pull-15')),
      'noceda_block_pull_16' => array('title' => t('Pull block with 16 columns'), 'class' => array('pull-16')),
      'noceda_block_pull_17' => array('title' => t('Pull block with 17 columns'), 'class' => array('pull-17')),
      'noceda_block_pull_18' => array('title' => t('Pull block with 18 columns'), 'class' => array('pull-18')),
      'noceda_block_pull_19' => array('title' => t('Pull block with 19 columns'), 'class' => array('pull-19')),
      'noceda_block_pull_20' => array('title' => t('Pull block with 20 columns'), 'class' => array('pull-20')),
      'noceda_block_pull_21' => array('title' => t('Pull block with 21 columns'), 'class' => array('pull-21')),
      'noceda_block_pull_22' => array('title' => t('Pull block with 22 columns'), 'class' => array('pull-22')),
      'noceda_block_pull_23' => array('title' => t('Pull block with 23 columns'), 'class' => array('pull-23')),
    ),
  );
  // Provides options to remove padding of div#block-content.
  $skins['groundwork_padding'] = array(
    'title' => t('Remove padding'),
    'description' => t('Removes content\'s padding. Useful if block contains only images, videos, slideshows, etc. in full width and height.'),
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 1,
      'negosyante' => 1,
      'nocedark' => 1,
      'mayumi' => 1,
      'kalikasan' => 1,
      'nyebe' => 1,
      'hatinggabi' => 1,
    ),
    'theme hooks' => array('block'),
    'group' => 'presentation',
    'options' => array(
      'noceda_padding_1' => array(
        'title' => t('Remove left and right padding.'),
        'class' => array('block-padding-h'),
      ),
      'noceda_padding_2' => array(
        'title' => t('Remove top and bottom padding.'),
        'class' => array('block-padding-v'),
      ),
    ),
  );
  // Provides options for different content alignment.
  $skins['groundwork_content_alignment'] = array(
    'title' => t('Content Alignment'),
    'type' => 'select',
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 1,
      'negosyante' => 1,
      'nocedark' => 1,
      'mayumi' => 1,
      'kalikasan' => 1,
      'nyebe' => 1,
      'hatinggabi' => 1,
    ),
    'group' => 'presentation',
    'options' => array(
      'noceda_content_alignment_1' => array('title' => t('Center content within its container'), 'class' => array('noceda-align-content-center')),
      'noceda_content_alignment_2' => array('title' => t('Align content to the left within its container'), 'class' => array('noceda-align-content-left')),
      'noceda_content_alignment_3' => array('title' => t('Align content to the right within its container'), 'class' => array('noceda-align-content-right')),
    ),
  );
  // Provides different options for menu styles.
  $skins['groundwork_menu_style'] = array(
    'title' => t('Menu Style'),
    'description' => t('Different style options for your menus.'),
    'type' => 'select',
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 1,
      'negosyante' => 1,
      'nocedark' => 1,
      'mayumi' => 1,
      'kalikasan' => 1,
      'nyebe' => 1,
      'hatinggabi' => 1,
    ),
    'theme hooks' => array('block__locale', 'block__system', 'block__shortcut', 'block__views', 'block__menu'),
    'group' => 'presentation',
    'options' => array(
      'noceda_menu_style_1' => array('title' => t('Horizontal inline menu'), 'class' => array('noceda-menu-style-inline', 'clearfix')),
      'noceda_menu_style_2' => array('title' => t('Multi-column menu with headers'), 'class' => array('noceda-menu-style-multi', 'clearfix')),
    ),
  );
  return $skins;
}
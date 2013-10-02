<?php

/**
 * @file
 * Implements hook_skinr_skin_info().
 */
function negosyante_skinr_skin_info() {
  // Provides options for different page background.
  $skins['negosyante_background'] = array(
    'title' => t('Background'),
    'type' => 'select',
    'default status' => 0,
    'status' => array(
      'bartik' => 0,
      'garland' => 0,
      'groundwork' => 0,
      'negosyante' => 1,
    ),
    'theme hooks' => array('block', 'page'),
    'group' => 'presentation',
    'attached' => array('css' => array('css/noceda-block-backgrounds.css')),
    'options' => array(
      'negosyante_bg_1' => array('title' => t('Clean White'), 'class' => array('noceda-bg-clean-white')),
      'negosyante_bg_2' => array('title' => t('Ash Grey'), 'class' => array('noceda-bg-ash-grey')),
      'negosyante_bg_3' => array('title' => t('Strawberry Pink'), 'class' => array('noceda-bg-strawberry-pink')),
      'negosyante_bg_4' => array('title' => t('Dainty Purple'), 'class' => array('noceda-bg-dainty-purple')),
      'negosyante_bg_5' => array('title' => t('Baby Blue'), 'class' => array('noceda-bg-baby-blue')),
      'negosyante_bg_6' => array('title' => t('Sea Cyan'), 'class' => array('noceda-bg-sea-cyan')),
      'negosyante_bg_7' => array('title' => t('Meadow Green'), 'class' => array('noceda-bg-meadow-green')),
      'negosyante_bg_8' => array('title' => t('Lemon Yellow'), 'class' => array('noceda-bg-lemon-yellow')),
    ),
  );
  return $skins;
}
<?php
// Change the theme functions that are being overridden
function beautytips_emvideo_admin_info() {
  $form['beautytips_emvideo'] = array(
    '#type' => 'fieldset',
    '#title' => 'Emvideo Tooltips',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['beautytips_emvideo']['beautytips_emvideo_alt_text'] = array(
    '#type' => 'checkbox',
    '#title' => 'Display Alternate Text beautytips with emvideo',
    '#default_value' => variable_get('beautytips_emvideo_alt_text', FALSE),
  );
  return $form;
}

function beautytips_emvideo_theme_change(&$theme_registry) {
  if (module_exists('emvideo') && variable_get('beautytips_emvideo_alt_text', FALSE)) {
    $theme_registry['emvideo_formatter_video_video']['function'] = 'theme_beautytips_emvideo_formatter_video_video';
    $theme_registry['emvideo_formatter_video_video']['file'] = drupal_get_path('module', 'beautytips') . '/includes/emvideo.inc';
   
    $theme_registry['emvideo_formatter_video_embed']['function'] = 'theme_beautytips_emvideo_formatter_video_embed';
    $theme_registry['emvideo_formatter_video_embed']['file'] = drupal_get_path('module', 'beautytips') . '/includes/emvideo.inc';
   
    $theme_registry['emvideo_formatter_default']['function'] = 'theme_beautytips_emvideo_formatter_default';
    $theme_registry['emvideo_formatter_default']['file'] = drupal_get_path('module', 'beautytips') . '/includes/emvideo.inc';
    
    $theme_registry['emvideo_formatter_video_preview']['function'] = 'theme_beautytips_emvideo_formatter_video_preview';
    $theme_registry['emvideo_formatter_video_preview']['file'] = drupal_get_path('module', 'beautytips') . '/includes/emvideo.inc';
    
    $theme_registry['emvideo_formatter_video_thumbnail']['function'] = 'theme_beautytips_emvideo_formatter_video_thumbnail';
    $theme_registry['emvideo_formatter_video_thumbnail']['file'] = drupal_get_path('module', 'beautytips') . '/includes/emvideo.inc';
      
    $theme_registry['emvideo_formatter_video_flash']['function'] = 'theme_beautytips_emvideo_formatter_video_flash';
    $theme_registry['emvideo_formatter_video_flash']['file'] = drupal_get_path('module', 'beautytips') . '/includes/emvideo.inc';
       
    $theme_registry['emvideo_formatter_thickbox']['function'] = 'theme_beautytips_emvideo_formatter_thickbox';
    $theme_registry['emvideo_formatter_thickbox']['file'] = drupal_get_path('module', 'beautytips') . '/includes/emvideo.inc';
        
    $theme_registry['emvideo_formatter_video_replace']['function'] = 'theme_beautytips_emvideo_formatter_video_replace';
    $theme_registry['emvideo_formatter_video_replace']['file'] = drupal_get_path('module', 'beautytips') . '/includes/emvideo.inc';
         
    $theme_registry['emvideo_formatter_video_replace_preview']['function'] = 'theme_beautytips_emvideo_formatter_video_replace_preview';
    $theme_registry['emvideo_formatter_video_replace_preview']['file'] = drupal_get_path('module', 'beautytips') . '/includes/emvideo.inc';
  }  
}

function theme_beautytips_emvideo_formatter_video_video($element) {
  $options = array();
  $options['bt_emfield_video'] = array(
    'cssSelect' => '.emvideo-thumbnail-replace-preview img',
    'contentSelector' => "$(this).attr('alt')",
    'trigger' => array(0 => 'mouseover', 1 => 'click'),
    'width' => 350,
  );
  beautytips_add_beautytips($options);
  $field = content_fields($element['#field_name'], $element['#type_name']);
  return module_invoke('emvideo', 'field_formatter', $field, $element['#item'], $element['#formatter'], $element['#node']);
}

function theme_beautytips_emvideo_formatter_video_embed($element) {
  $options = array();
  $options['bt_emfield_video'] = array(
    'cssSelect' => '.emvideo-thumbnail-replace-preview img',
    'contentSelector' => "$(this).attr('alt')",
    'trigger' => array(0 => 'mouseover', 1 => 'click'),
    'width' => 350,
  );
  beautytips_add_beautytips($options);
  $field = content_fields($element['#field_name'], $element['#type_name']);
  return module_invoke('emvideo', 'field_formatter', $field, $element['#item'], $element['#formatter'], $element['#node']);
}

function theme_beautytips_emvideo_formatter_default($element) {
  $options = array();
  $options['bt_emfield_video'] = array(
    'cssSelect' => '.emvideo-thumbnail-replace-preview img',
    'contentSelector' => "$(this).attr('alt')",
    'trigger' => array(0 => 'mouseover', 1 => 'click'),
    'width' => 350,
  );
  beautytips_add_beautytips($options);
  $field = content_fields($element['#field_name'], $element['#type_name']);
  return module_invoke('emvideo', 'field_formatter', $field, $element['#item'], $element['#formatter'], $element['#node']);
}

function theme_beautytips_emvideo_formatter_video_preview($element) {
  $options = array();
  $options['bt_emfield_video'] = array(
    'cssSelect' => '.emvideo-thumbnail-replace-preview img',
    'contentSelector' => "$(this).attr('alt')",
    'trigger' => array(0 => 'mouseover', 1 => 'click'),
    'width' => 350,
  );
  beautytips_add_beautytips($options);
  $field = content_fields($element['#field_name'], $element['#type_name']);
  return module_invoke('emvideo', 'field_formatter', $field, $element['#item'], $element['#formatter'], $element['#node']);
}

function theme_beautytips_emvideo_formatter_video_thumbnail($element) {
  $options = array();
  $options['bt_emfield_video'] = array(
    'cssSelect' => '.emvideo-thumbnail-replace-preview img',
    'contentSelector' => "$(this).attr('alt')",
    'trigger' => array(0 => 'mouseover', 1 => 'click'),
    'width' => 350,
  );
  beautytips_add_beautytips($options);
  $field = content_fields($element['#field_name'], $element['#type_name']);
  return module_invoke('emvideo', 'field_formatter', $field, $element['#item'], $element['#formatter'], $element['#node']);
}

function theme_beautytips_emvideo_formatter_video_flash($element) {
  $options = array();
  $options['bt_emfield_video'] = array(
    'cssSelect' => '.emvideo-thumbnail-replace-preview img',
    'contentSelector' => "$(this).attr('alt')",
    'trigger' => array(0 => 'mouseover', 1 => 'click'),
    'width' => 350,
  );
  beautytips_add_beautytips($options);
  $field = content_fields($element['#field_name'], $element['#type_name']);
  return module_invoke('emvideo', 'field_formatter', $field, $element['#item'], $element['#formatter'], $element['#node']);
}
function theme_beautytips_emvideo_formatter_thickbox($element) {
  $options = array();
  $options['bt_emfield_video'] = array(
    'cssSelect' => '.emvideo-thumbnail-replace-preview img',
    'contentSelector' => "$(this).attr('alt')",
    'trigger' => array(0 => 'mouseover', 1 => 'click'),
    'width' => 350,
  );
  beautytips_add_beautytips($options);
  $field = content_fields($element['#field_name'], $element['#type_name']);
  return module_invoke('emvideo', 'field_formatter', $field, $element['#item'], $element['#formatter'], $element['#node']);
}
function theme_beautytips_emvideo_formatter_video_replace($element) {
  $options = array();
  $options['bt_emfield_video'] = array(
    'cssSelect' => '.emvideo-thumbnail-replace-full img',
    'contentSelector' => "$(this).attr('alt')",
    'trigger' => array(0 => 'mouseover', 1 => 'click'),
    'width' => 350,
  );
  beautytips_add_beautytips($options);
  $field = content_fields($element['#field_name'], $element['#type_name']);
  return module_invoke('emvideo', 'field_formatter', $field, $element['#item'], $element['#formatter'], $element['#node']);
}
function theme_beautytips_emvideo_formatter_video_replace_preview($element) {
  $options = array();
  $options['bt_emfield_video'] = array(
    'cssSelect' => '.emvideo-thumbnail-replace-preview img',
    'contentSelector' => "$(this).attr('alt')",
    'trigger' => array(0 => 'mouseover', 1 => 'click'),
    'width' => 350,
  );
  beautytips_add_beautytips($options);
  $field = content_fields($element['#field_name'], $element['#type_name']);
  return module_invoke('emvideo', 'field_formatter', $field, $element['#item'], $element['#formatter'], $element['#node']);
}


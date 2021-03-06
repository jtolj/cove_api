<?php

function cove_api_admin_site_settings() {
  $form = array();
  
  $form['cove_api_settings'] = array(
    '#title' => 'PBS COVE API Settings',
    '#type' => 'fieldset'
  );
  
  $form['cove_api_settings']['cove_api_key'] = array(
    '#title' => 'PBS COVE API Key',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#description' => 'COVE API Key',
    '#default_value' => variable_get('cove_api_key'),
  );
  
  $form['cove_api_settings']['cove_api_secret'] = array(
    '#title' => 'PBS COVE API Secret',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#description' => 'COVE API Secret',
  );

  $form = system_settings_form($form);
  return $form;
}

/**
 * Implements hook_form_validate
 */
function cove_api_admin_site_settings_validate($form, &$form_state) {
  $values = $form_state['values'];
  $api_key = $values['cove_api_key'];
  $api_secret = $values['cove_api_secret'];
  $query = array();
  $response = cove_api_request('videos', array('filter_title' => 'nova'), 0 , $api_key, $api_secret);
  
  if (!$response) {
    form_set_error('cove_api_settings', 'Failed to connect to COVE API with those credentials.');
  }
  else {
    drupal_set_message('Successfully connected with COVE API. Settings have been saved.');
  }
}

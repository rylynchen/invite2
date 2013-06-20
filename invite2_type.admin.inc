<?php

/**
 * @file
 * Model type editing UI.
 */

/**
 * UI controller.
 */
class Invite2TypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage invite2 entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the invite2 type editing form.
 */
function invite2_type_form($form, &$form_state, $invite2_type, $op = 'edit') {

  if ($op == 'clone') {
    $invite2_type->label .= ' (cloned)';
    $invite2_type->type = '';
  }
  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $invite2_type->label,
    '#description' => t('The human-readable name of this invite2 type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($invite2_type->type) ? $invite2_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'invite2_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this invite2 type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save invite2 type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function invite2_type_form_submit(&$form, &$form_state) {
  $invite2_type = entity_ui_form_submit_build_entity($form, $form_state);
  $invite2_type->save();
  $form_state['redirect'] = 'admin/structure/invite2_types';
}

/**
 * Form API submit callback for the delete button.
 */
function invite2_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/invite2_types/manage/' . $form_state['invite2_type']->type . '/delete';
}

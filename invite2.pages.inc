<?php

/**
 * Page to add Invite2 Entities.
 */
function invite2_add_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);
  if (count($content) == 1) {
    $item = array_shift($content);
    drupal_goto($item['href']);
  }    
  return theme('invite2_add_list', array('content' => $content));
}

/**
 * Displays the list of available invite2 types for invite2 creation.
 *
 * @ingroup themeable
 */
function theme_invite2_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="invite2-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer invite2 types')) {
      $output = '<p>' . t('Invite2 Entities cannot be added because you have not created any invite2 types yet. Go to the <a href="@create-invite2-type">invite2 type creation page</a> to add a new invite2 type.', array('@create-invite2-type' => url('admin/structure/invite2_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No Invite2 types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * Returns a invite2 submission form.
 *
 * @param $type
 *   The invite2 type for the submitted invite2.
 *
 * @return
 *   The themed form.
 */
function invite2_add($type) {
  $types = invite2_get_types();
  $invite2 = invite2_create(array('type' => $type));
  drupal_set_title(t('Create @name invite', array('@name' => $types[$type]->label)), PASS_THROUGH);
  $output = drupal_get_form('invite2_form', $invite2);
  return $output;
}

/**
 * Sets up content to show an individual invite2
 * @todo - get rid of drupal_set_title();
 */
function invite2_page_view($invite2, $view_mode = 'full') {
  $controller = entity_get_controller('invite2');
  $content = $controller->view(array($invite2->iid => $invite2));
  drupal_set_title(t('Invite @email', array('@email' => $invite2->email)));
  return $content;
}

/**
 * Invite2 edit page.
 */
function invite2_page_edit($invite2) {
  return drupal_get_form('invite2_form', $invite2);
}

/**
 * Confirm form for deleting a invite2.
 */
function invite2_delete_confirm_form($form, &$form_state, $invite2) {
  $form_state += array('invite2' => $invite2);
  $confirm_question = t('Are you sure you want to delete invite2 for Email : %email ?', array('%email' => $invite2->email));
  return confirm_form($form, $confirm_question, 'invite2/'.$bmap->bid);
}

/**
 * Invite2 delete confirm form submit handler.
 */
function invite2_delete_confirm_form_submit($form, &$form_state) {
  $invite2 = $form_state['invite2'];
  $invite2->delete();
  drupal_set_message(t('Delete invite2 for Email : %email .', array('%email' => $invite2->email)));
  $form_state['redirect'] = 'admin/structure/invite2';
}
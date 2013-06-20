<?php

/**
 * Page to manage Invite2 Entities.
 */
function invite2_manage() {
  return 'invite2_manage';
  // $view = views_get_view('invite2s', 'default');
  // $view->override_url = $_GET['q'];
  // return $view->preview();
}

/**
 * Sets the breadcrumb for administrative invite2 pages.
 */
function invite2_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Invite2s'), 'admin/content/invite2s'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
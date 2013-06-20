<?php

/**
 * @file
 * Provides Entity metadata integration.
 */

/**
 * Extend the defaults.
 */
class Invite2MetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['email'] = array(
      'label' => t('Email'),
      'description' => t('The invitee email address.'),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer email',
      'schema field' => 'email',
    );
    return $info;
  }
}
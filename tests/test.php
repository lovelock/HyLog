<?php

$logger = new Hylog();
/*
 *$logger->setBasePath('/var/gggggg');
 *var_dump($logger->getBasePath());
 */
/*
 *$logger->log('a', 'b', array());
 *echo "\n";
 */

$logger->realLog("I am log" . PHP_EOL, 3, __DIR__ . "/vala.log");
/*
 *echo Hylog::EMERGENCY;
 *echo "\n";
 *echo Hylog::ALERT;
 *echo "\n";
 */

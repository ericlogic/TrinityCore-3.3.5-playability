DROP TABLE IF EXISTS `account_reward_points`;
CREATE TABLE `account_reward_points` (
  `accountId` int unsigned NOT NULL DEFAULT '0' COMMENT 'Account Identifier',
  `points` int NOT NULL DEFAULT '0' COMMENT 'Available Points',
  PRIMARY KEY (`accountId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

DROP TABLE IF EXISTS `reward_point_journal`;
CREATE TABLE `reward_point_journal` (
  `timestamp` datetime NOT NULL COMMENT 'Timestamp',
  `date` int unsigned NOT NULL COMMENT 'Date',
  `accountId` int unsigned NOT NULL COMMENT 'Account Identifier',
  `characterId` int unsigned NOT NULL COMMENT 'Character GUID',
  `cause` int unsigned NOT NULL COMMENT 'Cause',
  `targetId` int unsigned DEFAULT NULL COMMENT 'Target Identitfier',
  `points` int NOT NULL COMMENT 'Reward Points',
  KEY `accountId` (`accountId`,`cause`,`date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

DROP TABLE IF EXISTS `reward_point_coupon`;
CREATE TABLE `reward_point_coupon` (
  `id` int unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identitfier',
  `code` char(16) NOT NULL DEFAULT '' COMMENT 'Code for redeem',
  `points` int NOT NULL COMMENT 'Reward points',
  `total` int NOT NULL COMMENT 'Total redeem times',
  `rest` int NOT NULL COMMENT 'Rest redeem times',
  PRIMARY KEY (`id`),
  KEY `code` (`code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
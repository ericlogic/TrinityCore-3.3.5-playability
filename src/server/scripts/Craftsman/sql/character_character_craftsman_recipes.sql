DROP TABLE IF EXISTS `character_craftsman_recipes`;

CREATE TABLE `character_craftsman_recipes` (
  `guid` int unsigned NOT NULL COMMENT 'Global Unique Identifier',
  `recipeid` int unsigned NOT NULL COMMENT 'Recipe item template ID',
  `time` datetime DEFAULT NULL,
  PRIMARY KEY (`guid`,`recipeid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

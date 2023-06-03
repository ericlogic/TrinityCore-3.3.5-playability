DROP TABLE IF EXISTS `craftsman_text`;

CREATE TABLE `craftsman_text` (
  `id` int unsigned NOT NULL COMMENT 'Identity',
  `text` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Text',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Craftsman Text';

INSERT INTO `craftsman_text` (`id`, `text`)
VALUES
	(1000, 'Tailoring service'),
	(1001, 'Smelt ores'),
	(1002, 'Blacksmith service'),
	(1003, 'Leatherworking service'),
	(1100, 'Keyword: {0}'),
	(1101, '<Click here to enter keyword for search>'),
	(1102, 'You must supply {1} to make {0}.'),
	(1103, 'Your bag is full!'),
	(1104, '{0} is being made, please wait...'),
	(1105, 'I have a recipe.'),
	(1106, '<Back>'),
	(1107, 'You don\'t have such item.'),
	(1108, 'I\'ve learned it, thank you!'),
	(1109, 'Well!'),
	(1110, 'You are welcome!');

DROP TABLE IF EXISTS `craftsman_text_locale`;

CREATE TABLE `craftsman_text_locale` (
  `id` int unsigned NOT NULL COMMENT 'Identity',
  `locale` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL DEFAULT '' COMMENT 'Locale',
  `text` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL COMMENT 'Text',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci COMMENT='Craftsman Text Translations';

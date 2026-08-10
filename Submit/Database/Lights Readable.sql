DROP TABLE IF EXISTS `led_state`;
CREATE TABLE `led_state` (
  `led_id` int NOT NULL AUTO_INCREMENT,
  `room_id` int NOT NULL,
  `is_on` tinyint NOT NULL DEFAULT '0',
  `hue` smallint unsigned DEFAULT '0',
  `saturation` smallint unsigned DEFAULT '0',
  `value` smallint unsigned DEFAULT '0',
  `last_updated` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  UNIQUE KEY `room_id_UNIQUE` (`room_id`),
  UNIQUE KEY `led_id_UNIQUE` (`led_id`),
  CONSTRAINT `room_id` FOREIGN KEY (`room_id`) REFERENCES `rooms` (`room_id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS `motion_settings`;
CREATE TABLE `motion_settings` (
  `id` int NOT NULL AUTO_INCREMENT,
  `room_id` int NOT NULL,
  `motion_sensing_enabled` tinyint NOT NULL DEFAULT '1',
  `last_updated` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  KEY `rooms_id-motion_settings_idx` (`room_id`),
  CONSTRAINT `rooms_id-motion_settings` FOREIGN KEY (`room_id`) REFERENCES `rooms` (`room_id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS `occupancy`;
CREATE TABLE `occupancy` (
  `id` int NOT NULL AUTO_INCREMENT,
  `room_id` int NOT NULL,
  `people_count` int NOT NULL DEFAULT '0',
  `last_updated` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`),
  KEY `room_id_idx` (`room_id`),
  CONSTRAINT `room_id-occupancy` FOREIGN KEY (`room_id`) REFERENCES `rooms` (`room_id`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS `rooms`;
CREATE TABLE `rooms` (
  `room_id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `created_at` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`room_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

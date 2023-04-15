/*
 * Copyright (C) 2010 - 2017 Novatek, Inc.
 * Copyright (C) 2018 XiaoMi, Inc.
 *
 * $Revision: 14590 $
 * $Date: 2017-07-20 11:14:42 +0800 (周四, 20 七月 2017) $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 */

#if NVT_TOUCH_MP

static uint32_t IC_X_CFG_SIZE = 18;
static uint32_t IC_Y_CFG_SIZE = 32;
static uint32_t IC_KEY_CFG_SIZE = 4;
static uint32_t X_Channel = 18;
static uint32_t Y_Channel = 32;
static uint32_t Key_Channel = TOUCH_KEY_NUM;
static uint8_t AIN_X[40] = {17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static uint8_t AIN_Y[40] = {31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
#if TOUCH_KEY_NUM > 0
static uint8_t AIN_KEY[8] = {0, 1, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
#endif /* #if TOUCH_KEY_NUM > 0 */

static int32_t PS_Config_Lmt_Short_Rawdata_P = 14000;
static int32_t PS_Config_Lmt_Short_Rawdata_N = 11000;
static int32_t PS_Config_Lmt_Key_Short_Rawdata_P = 14000;
static int32_t PS_Config_Lmt_Key_Short_Rawdata_N = 11000;
static int32_t PS_Config_Lmt_Short_Diff_P = 6300;
static int32_t PS_Config_Lmt_Short_Diff_N;
static int32_t PS_Config_Lmt_Key_Short_Diff_P = 6300;
static int32_t PS_Config_Lmt_Key_Short_Diff_N;
static int32_t PS_Config_Lmt_Short_Base_P = 2000;
static int32_t PS_Config_Lmt_Short_Base_N = -2000;
static int32_t PS_Config_Lmt_Key_Short_Base_P = 2000;
static int32_t PS_Config_Lmt_Key_Short_Base_N = -2000;

static int32_t PS_Config_Lmt_Open_Rawdata_P[40 * 40] = {
	7336, 7373, 7385, 7397, 7412, 7435, 7446, 7427, 7402, 7363, 7393, 7410, 7431, 7448, 7430, 7415, 7400, 7387,
	7333, 7372, 7387, 7399, 7416, 7441, 7448, 7428, 7401, 7367, 7396, 7414, 7438, 7451, 7431, 7416, 7399, 7379,
	7326, 7363, 7377, 7390, 7406, 7435, 7437, 7417, 7390, 7377, 7406, 7425, 7449, 7458, 7441, 7423, 7407, 7384,
	7330, 7370, 7384, 7397, 7414, 7440, 7443, 7422, 7394, 7360, 7388, 7406, 7430, 7440, 7420, 7403, 7387, 7361,
	7341, 7383, 7401, 7415, 7433, 7458, 7459, 7437, 7409, 7376, 7405, 7425, 7450, 7454, 7436, 7419, 7402, 7371,
	7335, 7373, 7393, 7405, 7423, 7451, 7447, 7425, 7397, 7386, 7414, 7435, 7462, 7464, 7445, 7427, 7409, 7376,
	7348, 7387, 7410, 7425, 7442, 7471, 7464, 7441, 7413, 7384, 7413, 7432, 7458, 7460, 7440, 7423, 7403, 7367,
	7354, 7392, 7417, 7431, 7450, 7478, 7468, 7445, 7417, 7388, 7415, 7436, 7461, 7460, 7440, 7424, 7401, 7366,
	7341, 7377, 7405, 7420, 7438, 7465, 7455, 7431, 7404, 7405, 7435, 7456, 7483, 7477, 7457, 7439, 7413, 7376,
	7350, 7386, 7417, 7434, 7452, 7482, 7467, 7444, 7414, 7399, 7427, 7447, 7474, 7469, 7447, 7429, 7400, 7364,
	7359, 7397, 7427, 7448, 7466, 7498, 7480, 7456, 7426, 7412, 7443, 7464, 7491, 7480, 7460, 7440, 7408, 7371,
	7348, 7385, 7416, 7438, 7459, 7487, 7465, 7443, 7414, 7424, 7455, 7478, 7507, 7492, 7472, 7447, 7414, 7377,
	7363, 7401, 7432, 7459, 7479, 7512, 7486, 7461, 7432, 7420, 7451, 7472, 7501, 7485, 7464, 7436, 7404, 7366,
	7371, 7410, 7442, 7473, 7493, 7524, 7497, 7472, 7440, 7430, 7461, 7484, 7514, 7494, 7473, 7440, 7407, 7369,
	7364, 7403, 7433, 7465, 7490, 7517, 7489, 7464, 7434, 7458, 7491, 7516, 7548, 7522, 7497, 7461, 7428, 7389,
	7372, 7411, 7444, 7476, 7503, 7530, 7500, 7474, 7442, 7441, 7473, 7498, 7528, 7504, 7474, 7438, 7406, 7367,
	7387, 7426, 7461, 7495, 7526, 7552, 7521, 7494, 7459, 7465, 7500, 7525, 7556, 7526, 7494, 7456, 7423, 7381,
	7369, 7408, 7441, 7473, 7513, 7550, 7523, 7495, 7461, 7496, 7533, 7561, 7584, 7534, 7495, 7459, 7424, 7382,
	7392, 7432, 7467, 7502, 7542, 7580, 7555, 7524, 7488, 7499, 7537, 7564, 7581, 7533, 7491, 7456, 7420, 7379,
	7406, 7447, 7484, 7521, 7562, 7598, 7574, 7543, 7505, 7520, 7559, 7590, 7599, 7547, 7506, 7467, 7430, 7389,
	7409, 7451, 7487, 7524, 7569, 7599, 7580, 7547, 7509, 7552, 7594, 7624, 7630, 7575, 7532, 7490, 7452, 7407,
	7426, 7469, 7508, 7549, 7595, 7624, 7602, 7572, 7528, 7551, 7592, 7617, 7620, 7567, 7522, 7482, 7443, 7397,
	7444, 7490, 7530, 7573, 7622, 7650, 7628, 7596, 7551, 7587, 7630, 7657, 7656, 7598, 7552, 7508, 7469, 7420,
	7446, 7492, 7534, 7577, 7629, 7651, 7628, 7600, 7554, 7621, 7670, 7691, 7687, 7626, 7576, 7530, 7489, 7437,
	7479, 7529, 7574, 7621, 7676, 7696, 7671, 7644, 7595, 7635, 7680, 7702, 7693, 7631, 7581, 7535, 7492, 7439,
	7508, 7561, 7610, 7660, 7719, 7737, 7708, 7683, 7629, 7675, 7717, 7742, 7730, 7663, 7610, 7561, 7516, 7459,
	7502, 7556, 7604, 7658, 7718, 7729, 7701, 7676, 7626, 7724, 7768, 7797, 7777, 7706, 7647, 7595, 7547, 7486,
	7327, 7364, 7394, 7426, 7463, 7467, 7455, 7445, 7415, 7461, 7479, 7489, 7468, 7425, 7392, 7360, 7331, 7290,
	7385, 7427, 7462, 7500, 7546, 7549, 7533, 7518, 7487, 7534, 7557, 7572, 7547, 7496, 7457, 7420, 7385, 7338,
	7430, 7479, 7519, 7563, 7615, 7616, 7593, 7577, 7544, 7623, 7653, 7675, 7647, 7586, 7536, 7493, 7454, 7399,
	7506, 7563, 7613, 7669, 7732, 7732, 7703, 7679, 7641, 7695, 7730, 7758, 7727, 7656, 7600, 7550, 7505, 7445,
	7667, 7742, 7813, 7892, 7988, 7981, 7930, 7890, 7827, 7907, 7959, 8008, 7967, 7868, 7788, 7721, 7657, 7577,
#if TOUCH_KEY_NUM > 0
	13000, 13000, 13000,
#endif /* #if TOUCH_KEY_NUM > 0 */
};

static int32_t PS_Config_Lmt_Open_Rawdata_N[40 * 40] = {
	6829, 6851, 6858, 6864, 6873, 6886, 6893, 6881, 6867, 6845, 6862, 6872, 6884, 6893, 6883, 6875, 6866, 6859,
	6827, 6850, 6858, 6865, 6875, 6889, 6894, 6882, 6866, 6847, 6864, 6874, 6888, 6895, 6884, 6875, 6865, 6854,
	6824, 6845, 6853, 6860, 6869, 6886, 6887, 6876, 6860, 6853, 6869, 6880, 6894, 6899, 6890, 6879, 6870, 6857,
	6825, 6848, 6857, 6864, 6874, 6889, 6891, 6878, 6863, 6843, 6859, 6869, 6883, 6889, 6877, 6867, 6859, 6844,
	6832, 6856, 6867, 6874, 6885, 6900, 6900, 6887, 6871, 6852, 6869, 6880, 6894, 6897, 6887, 6877, 6867, 6849,
	6829, 6850, 6862, 6869, 6879, 6895, 6893, 6880, 6864, 6858, 6874, 6886, 6901, 6903, 6892, 6882, 6871, 6852,
	6836, 6858, 6872, 6880, 6890, 6906, 6903, 6889, 6873, 6857, 6873, 6884, 6899, 6900, 6889, 6879, 6868, 6847,
	6840, 6862, 6876, 6884, 6895, 6911, 6905, 6892, 6876, 6859, 6875, 6886, 6901, 6900, 6889, 6880, 6867, 6846,
	6832, 6852, 6869, 6877, 6888, 6903, 6897, 6884, 6868, 6869, 6886, 6898, 6914, 6910, 6899, 6889, 6873, 6852,
	6837, 6858, 6876, 6885, 6896, 6913, 6904, 6891, 6874, 6866, 6881, 6893, 6909, 6906, 6893, 6883, 6866, 6845,
	6842, 6864, 6881, 6894, 6904, 6922, 6912, 6898, 6881, 6873, 6890, 6902, 6919, 6912, 6901, 6889, 6870, 6849,
	6836, 6857, 6875, 6888, 6900, 6916, 6903, 6890, 6874, 6880, 6898, 6911, 6927, 6919, 6907, 6893, 6874, 6853,
	6845, 6866, 6884, 6900, 6911, 6930, 6916, 6901, 6884, 6878, 6895, 6907, 6924, 6915, 6903, 6886, 6868, 6846,
	6850, 6872, 6890, 6908, 6919, 6937, 6921, 6907, 6889, 6883, 6901, 6914, 6932, 6920, 6908, 6889, 6870, 6848,
	6845, 6867, 6885, 6903, 6918, 6933, 6917, 6903, 6885, 6900, 6918, 6932, 6951, 6936, 6921, 6901, 6882, 6859,
	6850, 6872, 6891, 6910, 6925, 6941, 6924, 6908, 6890, 6889, 6908, 6922, 6940, 6926, 6908, 6888, 6869, 6847,
	6859, 6881, 6901, 6921, 6939, 6953, 6936, 6920, 6900, 6903, 6923, 6938, 6956, 6938, 6920, 6898, 6879, 6855,
	6848, 6871, 6890, 6908, 6931, 6952, 6937, 6921, 6901, 6921, 6942, 6959, 6972, 6943, 6920, 6900, 6880, 6856,
	6861, 6885, 6904, 6924, 6948, 6969, 6955, 6937, 6917, 6923, 6945, 6960, 6970, 6942, 6918, 6898, 6877, 6854,
	6869, 6893, 6914, 6936, 6959, 6980, 6966, 6948, 6926, 6935, 6957, 6975, 6980, 6950, 6927, 6904, 6883, 6859,
	6871, 6895, 6916, 6937, 6963, 6980, 6969, 6951, 6929, 6954, 6977, 6995, 6998, 6966, 6942, 6918, 6896, 6870,
	6881, 6906, 6928, 6952, 6978, 6995, 6982, 6965, 6940, 6953, 6976, 6991, 6992, 6962, 6936, 6913, 6891, 6864,
	6891, 6917, 6941, 6966, 6994, 7009, 6997, 6979, 6953, 6974, 6998, 7013, 7013, 6980, 6953, 6928, 6906, 6877,
	6892, 6919, 6943, 6968, 6998, 7010, 6997, 6981, 6954, 6993, 7021, 7033, 7031, 6996, 6967, 6941, 6917, 6887,
	6911, 6940, 6966, 6993, 7025, 7036, 7022, 7006, 6978, 7001, 7027, 7040, 7035, 6999, 6970, 6943, 6919, 6888,
	6928, 6959, 6986, 7016, 7049, 7059, 7043, 7029, 6998, 7024, 7048, 7063, 7055, 7017, 6987, 6959, 6933, 6900,
	6924, 6956, 6983, 7014, 7049, 7055, 7039, 7025, 6996, 7052, 7077, 7094, 7083, 7042, 7008, 6978, 6950, 6915,
	6824, 6845, 6863, 6881, 6902, 6905, 6897, 6892, 6875, 6901, 6911, 6917, 6905, 6880, 6861, 6843, 6826, 6803,
	6857, 6881, 6902, 6924, 6950, 6951, 6942, 6934, 6916, 6943, 6956, 6965, 6951, 6921, 6899, 6877, 6858, 6830,
	6883, 6911, 6934, 6959, 6990, 6990, 6977, 6968, 6948, 6994, 7012, 7024, 7008, 6973, 6944, 6919, 6897, 6865,
	6927, 6960, 6988, 7020, 7057, 7057, 7040, 7026, 7005, 7035, 7056, 7072, 7054, 7013, 6981, 6952, 6926, 6892,
	7019, 7063, 7103, 7149, 7204, 7200, 7171, 7147, 7112, 7158, 7188, 7215, 7192, 7135, 7089, 7051, 7014, 6968,

#if TOUCH_KEY_NUM > 0
	6500, 6500, 6500,
#endif /* #if TOUCH_KEY_NUM > 0 */
};

static int32_t PS_Config_Lmt_FW_Rawdata_P[40 * 40] = {
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
	1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
#if TOUCH_KEY_NUM > 0
	2000, 2000, 2000,
#endif /* #if TOUCH_KEY_NUM > 0 */
};

static int32_t PS_Config_Lmt_FW_Rawdata_N[40 * 40] = {
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
	500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
#if TOUCH_KEY_NUM > 0
	400, 400, 400,
#endif /* #if TOUCH_KEY_NUM > 0 */
};

static int32_t PS_Config_Lmt_FW_CC_P = 119;
static int32_t PS_Config_Lmt_FW_CC_N = 72;
static int32_t PS_Config_Lmt_Key_FW_CC_P = 38;
static int32_t PS_Config_Lmt_Key_FW_CC_N = 9;
static int32_t PS_Config_Lmt_FW_CC_I_P = 25;
static int32_t PS_Config_Lmt_FW_CC_I_N;
static int32_t PS_Config_Lmt_FW_CC_Q_P = 25;
static int32_t PS_Config_Lmt_FW_CC_Q_N;
static int32_t PS_Config_Lmt_Key_FW_CC_I_P = 25;
static int32_t PS_Config_Lmt_Key_FW_CC_I_N;
static int32_t PS_Config_Lmt_Key_FW_CC_Q_P = 25;
static int32_t PS_Config_Lmt_Key_FW_CC_Q_N;

static int32_t PS_Config_Lmt_FW_Diff_P = 35;
static int32_t PS_Config_Lmt_FW_Diff_N = -35;
static int32_t PS_Config_Lmt_Key_FW_Diff_P = 35;
static int32_t PS_Config_Lmt_Key_FW_Diff_N = -35;

static int32_t PS_Config_Diff_Test_Frame = 50;

#endif /* #if NVT_TOUCH_MP */
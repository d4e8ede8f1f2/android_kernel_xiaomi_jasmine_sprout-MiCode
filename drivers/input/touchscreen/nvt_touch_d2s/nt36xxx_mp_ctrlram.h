/*
 * Copyright (C) 2010 - 2017 Novatek, Inc.
 * Copyright (C) 2019 XiaoMi, Inc.
 *
 * $Revision: 22093 $
 * $Date: 2018-01-24 13:51:33 +0800 (週三, 24 一月 2018) $
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

static int32_t PS_Config_Lmt_Short_Rawdata_P = 13500;
static int32_t PS_Config_Lmt_Short_Rawdata_N = 11500;
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
	7345, 7376, 7389, 7403, 7418, 7442, 7453, 7432, 7406, 7365, 7395, 7412, 7435, 7452, 7435, 7420, 7406, 7392,
	7342, 7378, 7393, 7407, 7425, 7450, 7458, 7436, 7407, 7365, 7393, 7412, 7437, 7450, 7433, 7418, 7402, 7380,
	7331, 7365, 7379, 7394, 7411, 7438, 7442, 7420, 7392, 7377, 7405, 7425, 7451, 7462, 7445, 7428, 7412, 7387,
	7333, 7371, 7387, 7402, 7420, 7446, 7448, 7426, 7397, 7362, 7389, 7408, 7434, 7444, 7425, 7409, 7393, 7367,
	7346, 7385, 7404, 7420, 7438, 7464, 7465, 7442, 7413, 7379, 7406, 7427, 7453, 7459, 7441, 7425, 7408, 7376,
	7334, 7370, 7390, 7405, 7423, 7451, 7447, 7425, 7395, 7389, 7417, 7438, 7466, 7469, 7450, 7434, 7417, 7382,
	7343, 7380, 7404, 7420, 7438, 7466, 7460, 7437, 7407, 7381, 7408, 7429, 7455, 7458, 7438, 7422, 7403, 7367,
	7351, 7387, 7413, 7429, 7448, 7477, 7467, 7444, 7413, 7384, 7412, 7433, 7460, 7458, 7440, 7424, 7403, 7366,
	7343, 7377, 7407, 7424, 7442, 7470, 7459, 7435, 7406, 7408, 7437, 7459, 7488, 7483, 7464, 7447, 7420, 7381,
	7351, 7386, 7417, 7437, 7456, 7486, 7470, 7446, 7416, 7394, 7423, 7443, 7472, 7467, 7446, 7429, 7399, 7363,
	7360, 7396, 7429, 7452, 7470, 7502, 7483, 7459, 7427, 7412, 7441, 7464, 7493, 7482, 7463, 7444, 7412, 7374,
	7348, 7384, 7416, 7440, 7460, 7489, 7466, 7444, 7413, 7422, 7453, 7475, 7506, 7492, 7473, 7450, 7416, 7378,
	7358, 7396, 7428, 7458, 7478, 7509, 7484, 7459, 7428, 7417, 7447, 7470, 7500, 7486, 7464, 7437, 7404, 7366,
	7372, 7410, 7443, 7477, 7497, 7528, 7500, 7474, 7441, 7428, 7459, 7483, 7515, 7495, 7474, 7443, 7410, 7371,
	7359, 7397, 7430, 7463, 7489, 7515, 7486, 7461, 7429, 7451, 7484, 7509, 7542, 7517, 7494, 7459, 7425, 7385,
	7373, 7411, 7445, 7480, 7507, 7534, 7503, 7477, 7443, 7440, 7472, 7497, 7530, 7505, 7476, 7442, 7408, 7369,
	7387, 7427, 7462, 7499, 7530, 7556, 7524, 7496, 7461, 7462, 7495, 7522, 7554, 7525, 7493, 7457, 7422, 7381,
	7369, 7407, 7441, 7476, 7516, 7553, 7525, 7497, 7462, 7493, 7530, 7559, 7582, 7533, 7495, 7459, 7423, 7382,
	7385, 7425, 7461, 7497, 7538, 7574, 7550, 7520, 7483, 7493, 7530, 7559, 7576, 7529, 7488, 7452, 7417, 7375,
	7403, 7445, 7482, 7522, 7564, 7599, 7577, 7544, 7505, 7514, 7553, 7585, 7594, 7543, 7502, 7464, 7427, 7384,
	7400, 7441, 7478, 7517, 7562, 7591, 7572, 7540, 7502, 7548, 7590, 7621, 7627, 7573, 7531, 7489, 7450, 7406,
	7421, 7464, 7504, 7546, 7592, 7621, 7600, 7569, 7526, 7545, 7587, 7613, 7615, 7564, 7519, 7479, 7440, 7395,
	7444, 7490, 7531, 7575, 7623, 7650, 7630, 7598, 7553, 7577, 7621, 7647, 7646, 7589, 7544, 7502, 7461, 7413,
	7442, 7489, 7531, 7575, 7626, 7647, 7626, 7598, 7553, 7615, 7664, 7686, 7682, 7621, 7572, 7527, 7485, 7435,
	7469, 7518, 7563, 7611, 7664, 7684, 7661, 7636, 7587, 7624, 7668, 7690, 7681, 7620, 7570, 7525, 7483, 7432,
	7501, 7554, 7602, 7653, 7711, 7729, 7702, 7678, 7625, 7664, 7706, 7731, 7717, 7653, 7599, 7552, 7507, 7452,
	7496, 7549, 7597, 7650, 7710, 7721, 7694, 7671, 7622, 7714, 7756, 7784, 7764, 7694, 7637, 7586, 7538, 7479,
	7325, 7362, 7392, 7425, 7461, 7466, 7454, 7445, 7416, 7453, 7471, 7481, 7460, 7418, 7384, 7354, 7325, 7285,
	7379, 7422, 7458, 7497, 7541, 7545, 7529, 7516, 7485, 7527, 7549, 7564, 7540, 7490, 7450, 7414, 7380, 7334,
	7419, 7467, 7508, 7552, 7604, 7604, 7583, 7568, 7537, 7612, 7641, 7662, 7633, 7573, 7526, 7483, 7444, 7391,
	7492, 7549, 7597, 7652, 7714, 7714, 7686, 7665, 7630, 7678, 7712, 7738, 7706, 7636, 7582, 7534, 7490, 7432,
	7652, 7728, 7798, 7877, 7968, 7965, 7917, 7879, 7823, 7890, 7941, 7985, 7944, 7848, 7770, 7702, 7641, 7558,
#if TOUCH_KEY_NUM > 0
	13000, 13000, 13000,
#endif /* #if TOUCH_KEY_NUM > 0 */
};

static int32_t PS_Config_Lmt_Open_Rawdata_N[40 * 40] = {
	6834, 6852, 6860, 6867, 6876, 6890, 6896, 6884, 6869, 6846, 6863, 6873, 6886, 6896, 6886, 6878, 6869, 6861,
	6833, 6853, 6862, 6870, 6880, 6895, 6900, 6887, 6870, 6846, 6862, 6873, 6887, 6895, 6885, 6876, 6867, 6854,
	6826, 6846, 6854, 6863, 6872, 6888, 6890, 6878, 6861, 6853, 6869, 6880, 6895, 6902, 6892, 6882, 6873, 6858,
	6828, 6849, 6858, 6867, 6877, 6892, 6894, 6881, 6864, 6844, 6860, 6871, 6885, 6891, 6880, 6871, 6862, 6847,
	6835, 6858, 6868, 6878, 6888, 6903, 6903, 6890, 6873, 6854, 6870, 6881, 6897, 6900, 6890, 6880, 6870, 6852,
	6828, 6848, 6860, 6869, 6879, 6895, 6893, 6880, 6863, 6859, 6876, 6888, 6904, 6905, 6895, 6886, 6875, 6855,
	6833, 6854, 6868, 6878, 6888, 6904, 6900, 6887, 6870, 6855, 6871, 6882, 6898, 6899, 6888, 6879, 6868, 6847,
	6838, 6858, 6874, 6883, 6894, 6910, 6905, 6891, 6874, 6857, 6873, 6885, 6901, 6899, 6889, 6880, 6868, 6847,
	6833, 6853, 6870, 6880, 6890, 6906, 6900, 6886, 6869, 6871, 6887, 6900, 6916, 6913, 6903, 6893, 6877, 6855,
	6838, 6858, 6876, 6887, 6898, 6915, 6906, 6892, 6875, 6863, 6879, 6891, 6907, 6904, 6892, 6883, 6866, 6845,
	6843, 6864, 6882, 6896, 6906, 6924, 6914, 6900, 6882, 6873, 6890, 6902, 6919, 6913, 6902, 6891, 6873, 6851,
	6836, 6857, 6875, 6889, 6901, 6917, 6904, 6891, 6874, 6879, 6896, 6909, 6927, 6919, 6908, 6895, 6875, 6853,
	6842, 6863, 6882, 6899, 6911, 6929, 6914, 6900, 6882, 6876, 6893, 6906, 6924, 6915, 6903, 6887, 6868, 6847,
	6850, 6872, 6891, 6910, 6921, 6939, 6923, 6909, 6890, 6882, 6900, 6914, 6932, 6921, 6909, 6891, 6871, 6849,
	6843, 6864, 6883, 6902, 6917, 6932, 6916, 6901, 6883, 6895, 6914, 6929, 6948, 6933, 6920, 6900, 6880, 6857,
	6850, 6872, 6892, 6912, 6928, 6943, 6925, 6910, 6891, 6889, 6907, 6922, 6941, 6926, 6910, 6890, 6871, 6848,
	6859, 6882, 6902, 6923, 6941, 6955, 6937, 6921, 6901, 6901, 6921, 6936, 6955, 6938, 6920, 6899, 6879, 6855,
	6848, 6870, 6889, 6910, 6933, 6954, 6938, 6922, 6902, 6919, 6940, 6957, 6971, 6943, 6920, 6900, 6879, 6855,
	6858, 6880, 6901, 6922, 6945, 6966, 6952, 6935, 6914, 6920, 6941, 6958, 6967, 6940, 6917, 6896, 6875, 6852,
	6868, 6892, 6913, 6936, 6960, 6981, 6967, 6949, 6926, 6931, 6954, 6972, 6978, 6948, 6925, 6903, 6882, 6857,
	6866, 6890, 6911, 6933, 6959, 6976, 6965, 6947, 6925, 6951, 6975, 6993, 6997, 6965, 6941, 6917, 6895, 6869,
	6878, 6903, 6926, 6950, 6976, 6993, 6981, 6963, 6939, 6949, 6974, 6988, 6990, 6960, 6934, 6912, 6889, 6863,
	6891, 6917, 6941, 6967, 6994, 7010, 6998, 6980, 6954, 6967, 6993, 7008, 7007, 6975, 6949, 6924, 6901, 6873,
	6890, 6917, 6941, 6966, 6996, 7008, 6996, 6980, 6954, 6990, 7017, 7030, 7028, 6993, 6965, 6939, 6915, 6886,
	6905, 6934, 6959, 6987, 7018, 7029, 7016, 7002, 6974, 6995, 7020, 7033, 7027, 6992, 6964, 6938, 6914, 6884,
	6924, 6954, 6982, 7012, 7045, 7055, 7039, 7026, 6995, 7018, 7042, 7056, 7048, 7011, 6981, 6953, 6927, 6896,
	6921, 6952, 6979, 7009, 7044, 7050, 7035, 7022, 6994, 7046, 7070, 7087, 7075, 7035, 7002, 6973, 6945, 6911,
	6823, 6844, 6862, 6880, 6901, 6904, 6897, 6892, 6875, 6896, 6907, 6912, 6900, 6876, 6857, 6840, 6823, 6800,
	6854, 6879, 6899, 6922, 6947, 6949, 6940, 6932, 6915, 6939, 6952, 6960, 6946, 6918, 6895, 6874, 6855, 6828,
	6877, 6905, 6928, 6953, 6983, 6983, 6971, 6962, 6944, 6988, 7005, 7016, 7000, 6965, 6938, 6914, 6891, 6861,
	6919, 6951, 6979, 7011, 7046, 7046, 7031, 7018, 6998, 7026, 7045, 7060, 7042, 7002, 6971, 6943, 6917, 6884,
	7011, 7055, 7095, 7140, 7192, 7191, 7163, 7141, 7109, 7148, 7177, 7202, 7178, 7123, 7079, 7040, 7004, 6957,
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

static int32_t PS_Config_Lmt_FW_CC_P = 132;
static int32_t PS_Config_Lmt_FW_CC_N = 74;
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

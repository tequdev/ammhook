#include "macro.h"

#define FLIP_ENDIAN_32(n)                                                      \
  ((uint32_t)(((n & 0xFFU) << 24U) | ((n & 0xFF00U) << 8U) |                   \
              ((n & 0xFF0000U) >> 8U) | ((n & 0xFF000000U) >> 24U)))

#define FLIP_ENDIAN_64(n)                                                      \
  ((uint64_t)(((n & 0xFFULL) << 56ULL) | ((n & 0xFF00ULL) << 40ULL) |          \
              ((n & 0xFF0000ULL) << 24ULL) | ((n & 0xFF000000ULL) << 8ULL) |   \
              ((n & 0xFF00000000ULL) >> 8ULL) |                                \
              ((n & 0xFF0000000000ULL) >> 24ULL) |                             \
              ((n & 0xFF000000000000ULL) >> 40ULL) |                           \
              ((n & 0xFF00000000000000ULL) >> 56ULL)))

// clang-format off
#define DEFINE_MULTIPLE_FIELD_INDICEX_8(X)                                    \
  X(1) X(2) X(3) X(4) X(5) X(6) X(7) X(8)

#define DEFINE_MULTIPLE_FIELD_INDICEX_10(X)                                    \
  X(1) X(2) X(3) X(4) X(5) X(6) X(7) X(8) X(9) X(10)

#define DEFINE_MULTIPLE_FIELD_INDICEX_16(X)                                    \
  X(1) X(2) X(3) X(4) X(5) X(6) X(7) X(8) X(9) X(10) X(11) X(12) X(13) X(14)   \
  X(15) X(16)

#define DEFINE_MULTIPLE_FIELD_INDICEX_32(X)                                    \
  X(1) X(2) X(3) X(4) X(5) X(6) X(7) X(8) X(9) X(10) X(11) X(12) X(13) X(14)   \
  X(15) X(16) X(17) X(18) X(19) X(20) X(21) X(22) X(23) X(24) X(25) X(26) X(27)\
  X(28) X(29) X(30) X(31) X(32)

#define DEFINE_MULTIPLE_FIELD_INDICEX_64(X)                                    \
  X(1) X(2) X(3) X(4) X(5) X(6) X(7) X(8) X(9) X(10) X(11) X(12) X(13) X(14)   \
  X(15) X(16) X(17) X(18) X(19) X(20) X(21) X(22) X(23) X(24) X(25) X(26) X(27)\
  X(28) X(29) X(30) X(31) X(32) X(33) X(34) X(35) X(36) X(37) X(38) X(39) X(40) \
  X(41) X(42) X(43) X(44) X(45) X(46) X(47) X(48) X(49) X(50) X(51) X(52) X(53) \
  X(54) X(55) X(56) X(57) X(58) X(59) X(60) X(61) X(62) X(63) X(64)
// clang-format on

// clang-format off
#define DEFINE_VL_FIELD_INDICEX_32(X)                                    \
  X(1,1) X(2,1) X(3,1) X(4,1) X(5,1) X(6,1) X(7,1) X(8,1) X(9,1) X(10,1) X(11,1) X(12,1) X(13,1) X(14,1)   \
  X(15,1) X(16,1) X(17,1) X(18,1) X(19,1) X(20,1) X(21,1) X(22,1) X(23,1) X(24,1) X(25,1) X(26,1) X(27,1)\
  X(28,1) X(29,1) X(30,1) X(31,1) X(32,1)

#define DEFINE_VL_FIELD_INDICEX_64(X)                                    \
  X(1,1) X(2,1) X(3,1) X(4,1) X(5,1) X(6,1) X(7,1) X(8,1) X(9,1) X(10,1) X(11,1) X(12,1) X(13,1) X(14,1)   \
  X(15,1) X(16,1) X(17,1) X(18,1) X(19,1) X(20,1) X(21,1) X(22,1) X(23,1) X(24,1) X(25,1) X(26,1) X(27,1)\
  X(28,1) X(29,1) X(30,1) X(31,1) X(32,1) X(33,1) X(34,1) X(35,1) X(36,1) X(37,1) X(38,1) X(39,1) X(40,1) \
  X(41,1) X(42,1) X(43,1) X(44,1) X(45,1) X(46,1) X(47,1) X(48,1) X(49,1) X(50,1) X(51,1) X(52,1) X(53,1) \
  X(54,1) X(55,1) X(56,1) X(57,1) X(58,1) X(59,1) X(60,1) X(61,1) X(62,1) X(63,1) X(64,1)

#define DEFINE_VL_FIELD_INDICEX_128(X)                                   \
  X(1,1) X(2,1) X(3,1) X(4,1) X(5,1) X(6,1) X(7,1) X(8,1) X(9,1) X(10,1) X(11,1) X(12,1) X(13,1) X(14,1)   \
  X(15,1) X(16,1) X(17,1) X(18,1) X(19,1) X(20,1) X(21,1) X(22,1) X(23,1) X(24,1) X(25,1) X(26,1) X(27,1)\
  X(28,1) X(29,1) X(30,1) X(31,1) X(32,1) X(33,1) X(34,1) X(35,1) X(36,1) X(37,1) X(38,1) X(39,1) X(40,1) \
  X(41,1) X(42,1) X(43,1) X(44,1) X(45,1) X(46,1) X(47,1) X(48,1) X(49,1) X(50,1) X(51,1) X(52,1) X(53,1) \
  X(54,1) X(55,1) X(56,1) X(57,1) X(58,1) X(59,1) X(60,1) X(61,1) X(62,1) X(63,1) X(64,1) X(65,1) X(66,1) X(67,1)\
  X(68,1) X(69,1) X(70,1) X(71,1) X(72,1) X(73,1) X(74,1) X(75,1) X(76,1) X(77,1) X(78,1) X(79,1) X(80,1) \
  X(81,1) X(82,1) X(83,1) X(84,1) X(85,1) X(86,1) X(87,1) X(88,1) X(89,1) X(90,1) X(91,1) X(92,1) X(93,1) \
  X(94,1) X(95,1) X(96,1) X(97,1) X(98,1) X(99,1) X(100,1) X(101,1) X(102,1) X(103,1) X(104,1) X(105,1) \
  X(106,1) X(107,1) X(108,1) X(109,1) X(110,1) X(111,1) X(112,1) X(113,1) X(114,1) X(115,1) X(116,1) X(117,1) \
  X(118,1) X(119,1) X(120,1) X(121,1) X(122,1) X(123,1) X(124,1) X(125,1) X(126,1) X(127,1) X(128,1) 

#define DEFINE_VL_FIELD_INDICEX_256(X)                                   \
  X(1,1) X(2,1) X(3,1) X(4,1) X(5,1) X(6,1) X(7,1) X(8,1) X(9,1) X(10,1) X(11,1) X(12,1) X(13,1) X(14,1)   \
  X(15,1) X(16,1) X(17,1) X(18,1) X(19,1) X(20,1) X(21,1) X(22,1) X(23,1) X(24,1) X(25,1) X(26,1) X(27,1)\
  X(28,1) X(29,1) X(30,1) X(31,1) X(32,1) X(33,1) X(34,1) X(35,1) X(36,1) X(37,1) X(38,1) X(39,1) X(40,1) \
  X(41,1) X(42,1) X(43,1) X(44,1) X(45,1) X(46,1) X(47,1) X(48,1) X(49,1) X(50,1) X(51,1) X(52,1) X(53,1) \
  X(54,1) X(55,1) X(56,1) X(57,1) X(58,1) X(59,1) X(60,1) X(61,1) X(62,1) X(63,1) X(64,1) X(65,1) X(66,1) X(67,1)\
  X(68,1) X(69,1) X(70,1) X(71,1) X(72,1) X(73,1) X(74,1) X(75,1) X(76,1) X(77,1) X(78,1) X(79,1) X(80,1) \
  X(81,1) X(82,1) X(83,1) X(84,1) X(85,1) X(86,1) X(87,1) X(88,1) X(89,1) X(90,1) X(91,1) X(92,1) X(93,1) \
  X(94,1) X(95,1) X(96,1) X(97,1) X(98,1) X(99,1) X(100,1) X(101,1) X(102,1) X(103,1) X(104,1) X(105,1) \
  X(106,1) X(107,1) X(108,1) X(109,1) X(110,1) X(111,1) X(112,1) X(113,1) X(114,1) X(115,1) X(116,1) X(117,1) \
  X(118,1) X(119,1) X(120,1) X(121,1) X(122,1) X(123,1) X(124,1) X(125,1) X(126,1) X(127,1) X(128,1)  \
    X(129,1) X(130,1) X(131,1) X(132,1) X(133,1) X(134,1) X(135,1) X(136,1) X(137,1) X(138,1) X(139,1) X(140,1) \
  X(141,1) X(142,1) X(143,1) X(144,1) X(145,1) X(146,1) X(147,1) X(148,1) X(149,1) X(150,1) X(151,1) X(152,1) \
  X(153,1) X(154,1) X(155,1) X(156,1) X(157,1) X(158,1) X(159,1) X(160,1) X(161,1) X(162,1) X(163,1) X(164,1) \
  X(165,1) X(166,1) X(167,1) X(168,1) X(169,1) X(170,1) X(171,1) X(172,1) X(173,1) X(174,1) X(175,1) X(176,1) \
  X(177,1) X(178,1) X(179,1) X(180,1) X(181,1) X(182,1) X(183,1) X(184,1) X(185,1) X(186,1) X(187,1) X(188,1) \
  X(189,1) X(190,1) X(191,1) X(192,1) X(193,2) X(194,2) X(195,2) X(196,2) X(197,2) X(198,2) X(199,2) X(200,2) \
  X(201,2) X(202,2) X(203,2) X(204,2) X(205,2) X(206,2) X(207,2) X(208,2) X(209,2) X(210,2) X(211,2) X(212,2) \
  X(213,2) X(214,2) X(215,2) X(216,2) X(217,2) X(218,2) X(219,2) X(220,2) X(221,2) X(222,2) X(223,2) X(224,2) \
  X(225,2) X(226,2) X(227,2) X(228,2) X(229,2) X(230,2) X(231,2) X(232,2) X(233,2) X(234,2) X(235,2) X(236,2) \
  X(237,2) X(238,2) X(239,2) X(240,2) X(241,2) X(242,2) X(243,2) X(244,2) X(245,2) X(246,2) X(247,2) X(248,2) \
  X(249,2) X(250,2) X(251,2) X(252,2) X(253,2) X(254,2) X(255,2) X(256,2)
  
#define DEFINE_VL_FIELD_INDICEX_512(X)                                   \
  X(1,1) X(2,1) X(3,1) X(4,1) X(5,1) X(6,1) X(7,1) X(8,1) X(9,1) X(10,1) X(11,1) X(12,1) X(13,1) X(14,1)   \
  X(15,1) X(16,1) X(17,1) X(18,1) X(19,1) X(20,1) X(21,1) X(22,1) X(23,1) X(24,1) X(25,1) X(26,1) X(27,1)\
  X(28,1) X(29,1) X(30,1) X(31,1) X(32,1) X(33,1) X(34,1) X(35,1) X(36,1) X(37,1) X(38,1) X(39,1) X(40,1) \
  X(41,1) X(42,1) X(43,1) X(44,1) X(45,1) X(46,1) X(47,1) X(48,1) X(49,1) X(50,1) X(51,1) X(52,1) X(53,1) \
  X(54,1) X(55,1) X(56,1) X(57,1) X(58,1) X(59,1) X(60,1) X(61,1) X(62,1) X(63,1) X(64,1) X(65,1) X(66,1) X(67,1)\
  X(68,1) X(69,1) X(70,1) X(71,1) X(72,1) X(73,1) X(74,1) X(75,1) X(76,1) X(77,1) X(78,1) X(79,1) X(80,1) \
  X(81,1) X(82,1) X(83,1) X(84,1) X(85,1) X(86,1) X(87,1) X(88,1) X(89,1) X(90,1) X(91,1) X(92,1) X(93,1) \
  X(94,1) X(95,1) X(96,1) X(97,1) X(98,1) X(99,1) X(100,1) X(101,1) X(102,1) X(103,1) X(104,1) X(105,1) \
  X(106,1) X(107,1) X(108,1) X(109,1) X(110,1) X(111,1) X(112,1) X(113,1) X(114,1) X(115,1) X(116,1) X(117,1) \
  X(118,1) X(119,1) X(120,1) X(121,1) X(122,1) X(123,1) X(124,1) X(125,1) X(126,1) X(127,1) X(128,1)  \
    X(129,1) X(130,1) X(131,1) X(132,1) X(133,1) X(134,1) X(135,1) X(136,1) X(137,1) X(138,1) X(139,1) X(140,1) \
  X(141,1) X(142,1) X(143,1) X(144,1) X(145,1) X(146,1) X(147,1) X(148,1) X(149,1) X(150,1) X(151,1) X(152,1) \
  X(153,1) X(154,1) X(155,1) X(156,1) X(157,1) X(158,1) X(159,1) X(160,1) X(161,1) X(162,1) X(163,1) X(164,1) \
  X(165,1) X(166,1) X(167,1) X(168,1) X(169,1) X(170,1) X(171,1) X(172,1) X(173,1) X(174,1) X(175,1) X(176,1) \
  X(177,1) X(178,1) X(179,1) X(180,1) X(181,1) X(182,1) X(183,1) X(184,1) X(185,1) X(186,1) X(187,1) X(188,1) \
  X(189,1) X(190,1) X(191,1) X(192,1) X(193,2) X(194,2) X(195,2) X(196,2) X(197,2) X(198,2) X(199,2) X(200,2) \
  X(201,2) X(202,2) X(203,2) X(204,2) X(205,2) X(206,2) X(207,2) X(208,2) X(209,2) X(210,2) X(211,2) X(212,2) \
  X(213,2) X(214,2) X(215,2) X(216,2) X(217,2) X(218,2) X(219,2) X(220,2) X(221,2) X(222,2) X(223,2) X(224,2) \
  X(225,2) X(226,2) X(227,2) X(228,2) X(229,2) X(230,2) X(231,2) X(232,2) X(233,2) X(234,2) X(235,2) X(236,2) \
  X(237,2) X(238,2) X(239,2) X(240,2) X(241,2) X(242,2) X(243,2) X(244,2) X(245,2) X(246,2) X(247,2) X(248,2) \
  X(249,2) X(250,2) X(251,2) X(252,2) X(253,2) X(254,2) X(255,2) X(256,2) X(257,2) X(258,2) X(259,2) X(260,2) \
  X(261,2) X(262,2) X(263,2) X(264,2) X(265,2) X(266,2) X(267,2) X(268,2) X(269,2) X(270,2) X(271,2) X(272,2) \
  X(273,2) X(274,2) X(275,2) X(276,2) X(277,2) X(278,2) X(279,2) X(280,2) X(281,2) X(282,2) X(283,2) X(284,2) \
  X(285,2) X(286,2) X(287,2) X(288,2) X(289,2) X(290,2) X(291,2) X(292,2) X(293,2) X(294,2) X(295,2) X(296,2) \
  X(297,2) X(298,2) X(299,2) X(300,2) X(301,2) X(302,2) X(303,2) X(304,2) X(305,2) X(306,2) X(307,2) X(308,2) \
  X(309,2) X(310,2) X(311,2) X(312,2) X(313,2) X(314,2) X(315,2) X(316,2) X(317,2) X(318,2) X(319,2) X(320,2) \
  X(321,2) X(322,2) X(323,2) X(324,2) X(325,2) X(326,2) X(327,2) X(328,2) X(329,2) X(330,2) X(331,2) X(332,2) \
  X(333,2) X(334,2) X(335,2) X(336,2) X(337,2) X(338,2) X(339,2) X(340,2) X(341,2) X(342,2) X(343,2) X(344,2) \
  X(345,2) X(346,2) X(347,2) X(348,2) X(349,2) X(350,2) X(351,2) X(352,2) X(353,2) X(354,2) X(355,2) X(356,2) \
  X(357,2) X(358,2) X(359,2) X(360,2) X(361,2) X(362,2) X(363,2) X(364,2) X(365,2) X(366,2) X(367,2) X(368,2) \
  X(369,2) X(370,2) X(371,2) X(372,2) X(373,2) X(374,2) X(375,2) X(376,2) X(377,2) X(378,2) X(379,2) X(380,2) \
  X(381,2) X(382,2) X(383,2) X(384,2) X(385,2) X(386,2) X(387,2) X(388,2) X(389,2) X(390,2) X(391,2) X(392,2) \
  X(393,2) X(394,2) X(395,2) X(396,2) X(397,2) X(398,2) X(399,2) X(400,2) X(401,2) X(402,2) X(403,2) X(404,2) \
  X(405,2) X(406,2) X(407,2) X(408,2) X(409,2) X(410,2) X(411,2) X(412,2) X(413,2) X(414,2) X(415,2) X(416,2) \
  X(417,2) X(418,2) X(419,2) X(420,2) X(421,2) X(422,2) X(423,2) X(424,2) X(425,2) X(426,2) X(427,2) X(428,2) \
  X(429,2) X(430,2) X(431,2) X(432,2) X(433,2) X(434,2) X(435,2) X(436,2) X(437,2) X(438,2) X(439,2) X(440,2) \
  X(441,2) X(442,2) X(443,2) X(444,2) X(445,2) X(446,2) X(447,2) X(448,2) X(449,2) X(450,2) X(451,2) X(452,2) \
  X(453,2) X(454,2) X(455,2) X(456,2) X(457,2) X(458,2) X(459,2) X(460,2) X(461,2) X(462,2) X(463,2) X(464,2) \
  X(465,2) X(466,2) X(467,2) X(468,2) X(469,2) X(470,2) X(471,2) X(472,2) X(473,2) X(474,2) X(475,2) X(476,2) \
  X(477,2) X(478,2) X(479,2) X(480,2) X(481,2) X(482,2) X(483,2) X(484,2) X(485,2) X(486,2) X(487,2) X(488,2) \
  X(489,2) X(490,2) X(491,2) X(492,2) X(493,2) X(494,2) X(495,2) X(496,2) X(497,2) X(498,2) X(499,2) X(500,2) \
  X(501,2) X(502,2) X(503,2) X(504,2) X(505,2) X(506,2) X(507,2) X(508,2) X(509,2) X(510,2) X(511,2) X(512,2)
// clang-format on

enum SerializedTypeID {
  // special types
  STI_UNKNOWN = -2,
  STI_NOTPRESENT = 0,

  // types (common)
  STI_UINT16 = 1,
  STI_UINT32 = 2,
  STI_UINT64 = 3,
  STI_UINT128 = 4,
  STI_UINT256 = 5,
  STI_AMOUNT = 6,
  STI_VL = 7,
  STI_ACCOUNT = 8,
  // 9-13 are reserved
  STI_OBJECT = 14,
  STI_ARRAY = 15,

  // types (uncommon)
  STI_UINT8 = 16,
  STI_UINT160 = 17,
  STI_PATHSET = 18,
  STI_VECTOR256 = 19,
  STI_UINT96 = 20,
  STI_UINT192 = 21,
  STI_UINT384 = 22,
  STI_UINT512 = 23,

  // high level types
  // cannot be serialized inside other types
  STI_TRANSACTION = 10001,
  STI_LEDGERENTRY = 10002,
  STI_VALIDATION = 10003,
  STI_METADATA = 10004,
};

#define FIELD_CODE(sfcode) (sfcode & 0xFFFF)
#define TYPE_CODE(sfcode) (sfcode >> 16)

constexpr uint16_t field_size_by_sto(uint32_t sfcode) {
  switch (TYPE_CODE(sfcode)) {
  case STI_UINT16:
    return 2;
  case STI_UINT32:
    return 4;
  case STI_UINT64:
    return 8;
  case STI_UINT128:
    return 16;
  case STI_UINT256:
    return 32;
  case STI_AMOUNT:
    return 48;
  case STI_VL: {
    switch (sfcode) {
    case sfSigningPubKey:
      return 33;
    default:
      // TODO
      return 1;
    }
  }
  case STI_ACCOUNT:
    return 20;
  case STI_OBJECT: {
    switch (sfcode) {
    case sfEmitDetails:
      return 116 + 22 - 3;
    default:
      // TODO
      return 1;
    }
  }
  case STI_ARRAY:
    // TODO
    return 1;
  case STI_UINT8:
    return 1;
  case STI_UINT160:
    return 20;
  case STI_PATHSET:
    // TODO
    return 1;
  case STI_VECTOR256:
    // TODO
    return 32;
  case STI_UINT96:
    return 12;
  case STI_UINT192:
    return 24;
  case STI_UINT384:
    return 48;
  case STI_UINT512:
    return 64;
  default:
    return 0;
  }
}

template <uint32_t sfcode, uint16_t SIZE = 0> struct TemplateField {};
// template <uint32_t sfcode> struct Field {};
template <uint32_t sfcode, uint16_t SIZE = 0> struct OptionalTemplateField {};
// template <uint32_t sfcode> struct OptionalField {};

#define CODE_SIZE(sfcode)                                                      \
  (1 + (TYPE_CODE(sfcode) >= 16 ? 1 : 0) + (FIELD_CODE(sfcode) >= 16 ? 1 : 0))

#define CODE_VALUE_1_1(sfcode)                                                 \
  { TYPE_CODE(sfcode) << 4 | FIELD_CODE(sfcode) }
#define CODE_VALUE_1_2(sfcode)                                                 \
  { TYPE_CODE(sfcode) << 4, FIELD_CODE(sfcode) }
#define CODE_VALUE_2_1(sfcode)                                                 \
  { FIELD_CODE(sfcode), TYPE_CODE(sfcode) }
#define CODE_VALUE_2_2(sfcode)                                                 \
  { 0x00, TYPE_CODE(sfcode), FIELD_CODE(sfcode) }

// TODO: Optional fields
#define CODE_OPTIONAL_VALUE_1_1(sfcode)                                        \
  { 0x99 }
#define CODE_OPTIONAL_VALUE_1_2(sfcode)                                        \
  { 0x99, 0x99 }
#define CODE_OPTIONAL_VALUE_2_1(sfcode)                                        \
  { 0x99, 0x99 }
#define CODE_OPTIONAL_VALUE_2_2(sfcode)                                        \
  { 0x99, 0x99, 0x99 }

// #define DEFINE_XXX_FIELD(sfcode, TYPE)                                         \
//   template <> struct TemplateField<sfcode> {                                           \
//     uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
//     uint8_t value[field_size_by_sto(sfcode)];                                  \
//   };                                                                           \
//   template <> struct OptionalTemplateField<sfcode> {                                   \
//     uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_2_##TYPE(sfcode);    \
//     uint8_t value[field_size_by_sto(sfcode)] = {[0 ... (field_size_by_sto(sfcode)-1)] = 0x99};                   \
//   };

#define DEFINE_UINT8_FIELD(sfcode, TYPE)                                       \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_2_##TYPE(sfcode);    \
    uint8_t value[field_size_by_sto(sfcode)] = {                               \
        [0 ...(field_size_by_sto(sfcode) - 1)] = 0x99};                        \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
    }                                                                          \
  };

#define DEFINE_UINT16_FIELD(sfcode, TYPE)                                      \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t value[field_size_by_sto(sfcode)] = {                               \
        [0 ...(field_size_by_sto(sfcode) - 1)] = 0x99};                        \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
    }                                                                          \
  };

#define DEFINE_UINT32_FIELD(sfcode, TYPE)                                      \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
    void setUint32(uint32_t value) {                                           \
      *(uint32_t *)(this->value) = FLIP_ENDIAN_32(value);                      \
    }                                                                          \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t value[field_size_by_sto(sfcode)] = {                               \
        [0 ...(field_size_by_sto(sfcode) - 1)] = 0x99};                        \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
    }                                                                          \
    void setUint32(uint32_t value) {                                           \
      *(uint32_t *)(this->value) = FLIP_ENDIAN_32(value);                      \
    }                                                                          \
  };

#define DEFINE_UINT64_FIELD(sfcode, TYPE)                                      \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
    void setUint64(uint64_t value) {                                           \
      *(uint64_t *)(this->value) = FLIP_ENDIAN_64(value);                      \
    }                                                                          \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t value[field_size_by_sto(sfcode)] = {                               \
        [0 ...(field_size_by_sto(sfcode) - 1)] = 0x99};                        \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
    }                                                                          \
    void setUint64(uint64_t value) {                                           \
      *(uint64_t *)(this->value) = FLIP_ENDIAN_64(value);                      \
    }                                                                          \
  };

#define DEFINE_UINT128_FIELD(sfcode, TYPE)                                     \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t value[field_size_by_sto(sfcode)] = {                               \
        [0 ...(field_size_by_sto(sfcode) - 1)] = 0x99};                        \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
    }                                                                          \
  };

#define DEFINE_UINT256_FIELD(sfcode, TYPE)                                     \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t value[field_size_by_sto(sfcode)] = {                               \
        [0 ...(field_size_by_sto(sfcode) - 1)] = 0x99};                        \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
    }                                                                          \
  };

// TODO: issuer, currency, value, setNativeAmount, setIOUAmount
#define DEFINE_AMOUNT_FIELD(sfcode, TYPE)                                      \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t value[8];                                                          \
    uint8_t currency[20];                                                      \
    uint8_t issuer[20];                                                        \
    inline void setNativeAmount(uint64_t drops) {                              \
      float_sto(SBUF(value), 0, 0, 0, 0, drops, 0);                                  \
    }                                                                          \
    inline void setIOUAmount(uint32_t c_ptr, uint32_t c_len, uint32_t i_ptr,   \
                             uint32_t i_len, uint64_t drops) {                 \
      float_sto((uint32_t)this, sizeof(this), c_ptr, c_ptr, i_ptr, i_len, drops, sfcode);  \
    }                                                                          \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t value[8] = {[0 ... 7] = 0x99};                                     \
    uint8_t currency[20] = {[0 ... 19] = 0x99};                                \
    uint8_t issuer[20] = {[0 ... 19] = 0x99};                                  \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
    }                                                                          \
    inline void setNativeAmount(uint64_t drops) {                              \
      float_sto(SBUF(value), 0, 0, 0, 0, drops, 0);                                  \
      useField();                                                              \
    }                                                                          \
    inline void setIOUAmount(uint32_t c_ptr, uint32_t c_len, uint32_t i_ptr,   \
                             uint32_t i_len, uint64_t drops) {                 \
      float_sto((uint32_t)this, sizeof(this), c_ptr, c_ptr, i_ptr, i_len, drops, sfcode);  \
      useField();                                                              \
    }                                                                          \
  };

#define DEFINE_NATIVE_AMOUNT_FIELD(sfcode, TYPE)                               \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t value[8] = {0x40};                                                 \
    void setDrops(uint64_t drops) {                                            \
      uint8_t *b = value;                                                      \
      *b++ = 0b01000000 + ((drops >> 56) & 0b00111111);                        \
      *b++ = (drops >> 48) & 0xFFU;                                            \
      *b++ = (drops >> 40) & 0xFFU;                                            \
      *b++ = (drops >> 32) & 0xFFU;                                            \
      *b++ = (drops >> 24) & 0xFFU;                                            \
      *b++ = (drops >> 16) & 0xFFU;                                            \
      *b++ = (drops >> 8) & 0xFFU;                                             \
      *b++ = (drops >> 0) & 0xFFU;                                             \
    }                                                                          \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t value[field_size_by_sto(sfcode)] = {                               \
        [0 ...(field_size_by_sto(sfcode) - 1)] = 0x99};                        \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
    }                                                                          \
    void setDrops(uint64_t drops) {                                            \
      uint8_t *b = value;                                                      \
      *b++ = 0b01000000 + ((drops >> 56) & 0b00111111);                        \
      *b++ = (drops >> 48) & 0xFFU;                                            \
      *b++ = (drops >> 40) & 0xFFU;                                            \
      *b++ = (drops >> 32) & 0xFFU;                                            \
      *b++ = (drops >> 24) & 0xFFU;                                            \
      *b++ = (drops >> 16) & 0xFFU;                                            \
      *b++ = (drops >> 8) & 0xFFU;                                             \
      *b++ = (drops >> 0) & 0xFFU;                                             \
    }                                                                          \
  };

// TODO: length
#define DEFINE_VL_FIELD_1(sfcode, TYPE, SIZE)                                  \
  template <> struct TemplateField<sfcode, SIZE> {                             \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t length[1] = {SIZE};                                                \
    uint8_t value[SIZE];                                                       \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode, SIZE> {                     \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t length[1] = {0x99};                                                \
    uint8_t value[SIZE] = {[0 ...(SIZE - 1)] = 0x99};                          \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
      length[0] = 0x00;                                                        \
    }                                                                          \
  };

// SIZE 7~390 (193~12480)
#define DEFINE_VL_FIELD_2(sfcode, TYPE, SIZE)                                  \
  template <> struct TemplateField<sfcode, SIZE> {                             \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t length[2] = {193 + static_cast<unsigned char>((SIZE - 193) >> 8),  \
                         (SIZE - 193) & 0xff};                                 \
    uint8_t value[SIZE] = {[0 ...(SIZE - 1)] = 0x99};                          \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode, SIZE> {                     \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t length[2] = {0x99, 0x99};                                          \
    uint8_t value[SIZE] = {[0 ...(SIZE - 1)] = 0x99};                          \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
      length[0] = 193 + static_cast<unsigned char>((SIZE - 193) >> 8);         \
      length[1] = (SIZE - 193) & 0xff;                                         \
    }                                                                          \
  };

#define DEFINE_ACCOUNT_FIELD(sfcode, TYPE)                                     \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t length[1] = {0x14};                                                \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t length[1] = {0x99};                                                \
    uint8_t value[field_size_by_sto(sfcode)] = {                               \
        [0 ...(field_size_by_sto(sfcode) - 1)] = 0x99};                        \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
      length[0] = 0x14;                                                        \
    }                                                                          \
  };

// TODO: value
#define DEFINE_OBJECT_FIELD(sfcode, TYPE, InnerFieldsStruct, InnerFieldName)   \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t prefix[1] = {0x7c};                                                \
    InnerFieldsStruct InnerFieldName;                                          \
    uint8_t postfix[1] = {0xe1};                                               \
  };
#define DEFINE_OPTIONAL_OBJECT_FIELD(sfcode, TYPE, InnerFieldsStruct,          \
                                     InnerFieldName)                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t prefix[1] = {0x99};                                                \
    InnerFieldsStruct InnerFieldName;                                          \
    uint8_t postfix[1] = {0x99};                                               \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
      prefix[0] = 0x7c;                                                        \
      postfix[0] = 0xe1;                                                       \
    }                                                                          \
  };

// TODO: value
#define DEFINE_ARRAY_FIELD(sfcode, TYPE, InnerFieldCode, SIZE)                 \
  template <> struct TemplateField<sfcode, SIZE> {                             \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);             \
    uint8_t prefix[1] = {0xf4};                                                \
    TemplateField<InnerFieldCode> values[SIZE];                                \
    uint8_t postfix[1] = {0xf1};                                               \
    TemplateField<InnerFieldCode> &operator[](uint16_t index) {                \
      return values[index];                                                    \
    }                                                                          \
    const TemplateField<InnerFieldCode> &operator[](uint16_t index) const {    \
      return values[index];                                                    \
    }                                                                          \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode, SIZE> {                     \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_1_##TYPE(sfcode);    \
    uint8_t prefix[1] = {0x99};                                                \
    OptionalTemplateField<InnerFieldCode> values[SIZE];                        \
    uint8_t postfix[1] = {0x99};                                               \
    OptionalTemplateField<InnerFieldCode> &operator[](uint16_t index) {        \
      return values[index];                                                    \
    }                                                                          \
    const OptionalTemplateField<InnerFieldCode> &                              \
    operator[](uint16_t index) const {                                         \
      return values[index];                                                    \
    }                                                                          \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_1_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
      prefix[0] = 0xf4;                                                        \
      postfix[0] = 0xf1;                                                       \
    }                                                                          \
  };

// TODO: issuer, currency?
#define DEFINE_UINT160_FIELD(sfcode, TYPE)                                     \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode> {                           \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_2_##TYPE(sfcode);    \
    uint8_t value[field_size_by_sto(sfcode)] = {                               \
        [0 ...(field_size_by_sto(sfcode) - 1)] = 0x99};                        \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
    }                                                                          \
  };

// TODO:
#define DEFINE_PATHSET_FIELD(sfcode, TYPE)                                     \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };

// TODO: length
// SIZE 1~6 (32~192)
#define DEFINE_VECTOR256_FIELD_1(sfcode, TYPE, SIZE)                           \
  template <> struct TemplateField<sfcode, SIZE> {                             \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
    uint8_t length[1] = {SIZE * 32};                                           \
    uint8_t value[SIZE][32];                                                   \
    void setValue(uint8_t index, uint8_t *newValue) {                          \
      unsigned char *buf = (unsigned char *)value[index];                      \
      *(uint64_t *)(buf + 0) = *(uint64_t *)(newValue + 0);                    \
      *(uint64_t *)(buf + 8) = *(uint64_t *)(newValue + 8);                    \
      *(uint64_t *)(buf + 16) = *(uint64_t *)(newValue + 16);                  \
      *(uint64_t *)(buf + 24) = *(uint64_t *)(newValue + 24);                  \
    }                                                                          \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode, SIZE> {                     \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_2_##TYPE(sfcode);    \
    uint8_t length[1] = {SIZE * 32};                                           \
    uint8_t value[SIZE][32] = {[0 ...(SIZE - 1)] = {[0 ...(32 - 1)] = 0x99}};  \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
      length[0] = SIZE * 32;                                                   \
    }                                                                          \
    void setValue(uint8_t index, uint8_t *newValue) {                          \
      unsigned char *buf = (unsigned char *)value[index];                      \
      *(uint64_t *)(buf + 0) = *(uint64_t *)(newValue + 0);                    \
      *(uint64_t *)(buf + 8) = *(uint64_t *)(newValue + 8);                    \
      *(uint64_t *)(buf + 16) = *(uint64_t *)(newValue + 16);                  \
      *(uint64_t *)(buf + 24) = *(uint64_t *)(newValue + 24);                  \
    }                                                                          \
  };

// SIZE 7~390 (193~12480)
#define DEFINE_VECTOR256_FIELD_2(sfcode, TYPE, SIZE)                           \
  template <> struct TemplateField<sfcode, SIZE> {                             \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
    uint8_t length[2] = {                                                      \
        193 + static_cast<unsigned char>((SIZE * 32 - 193) >> 8),              \
        (SIZE * 32 - 193) & 0xff};                                             \
    uint8_t value[SIZE][32];                                                   \
    void setValue(uint8_t index, uint8_t *newValue) {                          \
      unsigned char *buf = (unsigned char *)value[index];                      \
      *(uint64_t *)(buf + 0) = *(uint64_t *)(newValue + 0);                    \
      *(uint64_t *)(buf + 8) = *(uint64_t *)(newValue + 8);                    \
      *(uint64_t *)(buf + 16) = *(uint64_t *)(newValue + 16);                  \
      *(uint64_t *)(buf + 24) = *(uint64_t *)(newValue + 24);                  \
    }                                                                          \
  };                                                                           \
  template <> struct OptionalTemplateField<sfcode, SIZE> {                     \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_OPTIONAL_VALUE_2_##TYPE(sfcode);    \
    uint8_t length[2] = {0x99, 0x99};                                          \
    uint8_t value[SIZE][32] = {[0 ...(SIZE - 1)] = {[0 ...(32 - 1)] = 0x99}};  \
    inline void useField() {                                                   \
      uint8_t code_value[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);     \
      for (int i = 0; i < CODE_SIZE(sfcode); i++)                              \
        code[i] = code_value[i];                                               \
      length[0] = 193 + static_cast<unsigned char>((SIZE * 32 - 193) >> 8);    \
      length[1] = (SIZE * 32 - 193) & 0xff;                                    \
    }                                                                          \
    void setValue(uint8_t index, uint8_t *newValue) {                          \
      unsigned char *buf = (unsigned char *)value[index];                      \
      *(uint64_t *)(buf + 0) = *(uint64_t *)(newValue + 0);                    \
      *(uint64_t *)(buf + 8) = *(uint64_t *)(newValue + 8);                    \
      *(uint64_t *)(buf + 16) = *(uint64_t *)(newValue + 16);                  \
      *(uint64_t *)(buf + 24) = *(uint64_t *)(newValue + 24);                  \
    }                                                                          \
  };

#define DEFINE_UINT96_FIELD(sfcode, TYPE)                                      \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };

#define DEFINE_UINT192_FIELD(sfcode, TYPE)                                     \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };

#define DEFINE_UINT384_FIELD(sfcode, TYPE)                                     \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };

#define DEFINE_UINT512_FIELD(sfcode, TYPE)                                     \
  template <> struct TemplateField<sfcode> {                                   \
    uint8_t code[CODE_SIZE(sfcode)] = CODE_VALUE_2_##TYPE(sfcode);             \
    uint8_t value[field_size_by_sto(sfcode)];                                  \
  };

DEFINE_UINT8_FIELD(sfCloseResolution, 1)
DEFINE_UINT8_FIELD(sfMethod, 1)
DEFINE_UINT8_FIELD(sfTransactionResult, 1)
DEFINE_UINT8_FIELD(sfTickSize, 2)
DEFINE_UINT8_FIELD(sfUNLModifyDisabling, 2)
DEFINE_UINT8_FIELD(sfHookResult, 2)

DEFINE_UINT16_FIELD(sfLedgerEntryType, 1)
DEFINE_UINT16_FIELD(sfTransactionType, 1)
DEFINE_UINT16_FIELD(sfSignerWeight, 1)
DEFINE_UINT16_FIELD(sfTransferFee, 1)
DEFINE_UINT16_FIELD(sfVersion, 2)
DEFINE_UINT16_FIELD(sfHookStateChangeCount, 2)
DEFINE_UINT16_FIELD(sfHookEmitCount, 2)
DEFINE_UINT16_FIELD(sfHookExecutionIndex, 2)
DEFINE_UINT16_FIELD(sfHookApiVersion, 2)

DEFINE_UINT32_FIELD(sfNetworkID, 1)
DEFINE_UINT32_FIELD(sfFlags, 1)
DEFINE_UINT32_FIELD(sfSourceTag, 1)
DEFINE_UINT32_FIELD(sfSequence, 1)
DEFINE_UINT32_FIELD(sfPreviousTxnLgrSeq, 1)
DEFINE_UINT32_FIELD(sfLedgerSequence, 1)
DEFINE_UINT32_FIELD(sfCloseTime, 1)
DEFINE_UINT32_FIELD(sfParentCloseTime, 1)
DEFINE_UINT32_FIELD(sfSigningTime, 1)
DEFINE_UINT32_FIELD(sfExpiration, 1)
DEFINE_UINT32_FIELD(sfTransferRate, 1)
DEFINE_UINT32_FIELD(sfWalletSize, 1)
DEFINE_UINT32_FIELD(sfOwnerCount, 1)
DEFINE_UINT32_FIELD(sfDestinationTag, 1)
DEFINE_UINT32_FIELD(sfHighQualityIn, 2)
DEFINE_UINT32_FIELD(sfHighQualityOut, 2)
DEFINE_UINT32_FIELD(sfLowQualityIn, 2)
DEFINE_UINT32_FIELD(sfLowQualityOut, 2)
DEFINE_UINT32_FIELD(sfQualityIn, 2)
DEFINE_UINT32_FIELD(sfQualityOut, 2)
DEFINE_UINT32_FIELD(sfStampEscrow, 2)
DEFINE_UINT32_FIELD(sfBondAmount, 2)
DEFINE_UINT32_FIELD(sfLoadFee, 2)
DEFINE_UINT32_FIELD(sfOfferSequence, 2)
DEFINE_UINT32_FIELD(sfFirstLedgerSequence, 2)
DEFINE_UINT32_FIELD(sfLastLedgerSequence, 2)
DEFINE_UINT32_FIELD(sfTransactionIndex, 2)
DEFINE_UINT32_FIELD(sfOperationLimit, 2)
DEFINE_UINT32_FIELD(sfReferenceFeeUnits, 2)
DEFINE_UINT32_FIELD(sfReserveBase, 2)
DEFINE_UINT32_FIELD(sfReserveIncrement, 2)
DEFINE_UINT32_FIELD(sfSetFlag, 2)
DEFINE_UINT32_FIELD(sfClearFlag, 2)
DEFINE_UINT32_FIELD(sfSignerQuorum, 2)
DEFINE_UINT32_FIELD(sfCancelAfter, 2)
DEFINE_UINT32_FIELD(sfFinishAfter, 2)
DEFINE_UINT32_FIELD(sfSignerListID, 2)
DEFINE_UINT32_FIELD(sfSettleDelay, 2)
DEFINE_UINT32_FIELD(sfTicketCount, 2)
DEFINE_UINT32_FIELD(sfTicketSequence, 2)
DEFINE_UINT32_FIELD(sfNFTokenTaxon, 2)
DEFINE_UINT32_FIELD(sfMintedNFTokens, 2)
DEFINE_UINT32_FIELD(sfBurnedNFTokens, 2)
DEFINE_UINT32_FIELD(sfHookStateCount, 2)
DEFINE_UINT32_FIELD(sfEmitGeneration, 2)
DEFINE_UINT32_FIELD(sfLockCount, 2)
DEFINE_UINT32_FIELD(sfFirstNFTokenSequence, 2)
DEFINE_UINT32_FIELD(sfXahauActivationLgrSeq, 2)
DEFINE_UINT32_FIELD(sfImportSequence, 2)
DEFINE_UINT32_FIELD(sfRewardTime, 2)
DEFINE_UINT32_FIELD(sfRewardLgrFirst, 2)
DEFINE_UINT32_FIELD(sfRewardLgrLast, 2)

DEFINE_UINT64_FIELD(sfIndexNext, 1)
DEFINE_UINT64_FIELD(sfIndexPrevious, 1)
DEFINE_UINT64_FIELD(sfBookNode, 1)
DEFINE_UINT64_FIELD(sfOwnerNode, 1)
DEFINE_UINT64_FIELD(sfBaseFee, 1)
DEFINE_UINT64_FIELD(sfExchangeRate, 1)
DEFINE_UINT64_FIELD(sfLowNode, 1)
DEFINE_UINT64_FIELD(sfHighNode, 1)
DEFINE_UINT64_FIELD(sfDestinationNode, 1)
DEFINE_UINT64_FIELD(sfCookie, 1)
DEFINE_UINT64_FIELD(sfServerVersion, 1)
DEFINE_UINT64_FIELD(sfNFTokenOfferNode, 1)
DEFINE_UINT64_FIELD(sfEmitBurden, 1)

DEFINE_UINT64_FIELD(sfHookInstructionCount, 2)
DEFINE_UINT64_FIELD(sfHookReturnCode, 2)
DEFINE_UINT64_FIELD(sfReferenceCount, 2)
DEFINE_UINT64_FIELD(sfAccountIndex, 2)
DEFINE_UINT64_FIELD(sfAccountCount, 2)
DEFINE_UINT64_FIELD(sfRewardAccumulator, 2)

DEFINE_UINT128_FIELD(sfEmailHash, 1)

// DEFINE_UINT160_FIELD(sfTakerPaysCurrency, 1)
// DEFINE_UINT160_FIELD(sfTakerPaysIssuer, 1)
// DEFINE_UINT160_FIELD(sfTakerGetsCurrency, 1)
// DEFINE_UINT160_FIELD(sfTakerGetsIssuer, 1)

DEFINE_UINT256_FIELD(sfLedgerHash, 1)
DEFINE_UINT256_FIELD(sfParentHash, 1)
DEFINE_UINT256_FIELD(sfTransactionHash, 1)
DEFINE_UINT256_FIELD(sfAccountHash, 1)
DEFINE_UINT256_FIELD(sfPreviousTxnID, 1)
DEFINE_UINT256_FIELD(sfLedgerIndex, 1)
DEFINE_UINT256_FIELD(sfWalletLocator, 1)
DEFINE_UINT256_FIELD(sfRootIndex, 1)
DEFINE_UINT256_FIELD(sfAccountTxnID, 1)
DEFINE_UINT256_FIELD(sfNFTokenID, 1)
DEFINE_UINT256_FIELD(sfEmitParentTxnID, 1)
DEFINE_UINT256_FIELD(sfEmitNonce, 1)
DEFINE_UINT256_FIELD(sfEmitHookHash, 1)

DEFINE_UINT256_FIELD(sfBookDirectory, 2)
DEFINE_UINT256_FIELD(sfInvoiceID, 2)
DEFINE_UINT256_FIELD(sfNickname, 2)
DEFINE_UINT256_FIELD(sfAmendment, 2)
DEFINE_UINT256_FIELD(sfHookOn, 2)
DEFINE_UINT256_FIELD(sfDigest, 2)
DEFINE_UINT256_FIELD(sfChannel, 2)
DEFINE_UINT256_FIELD(sfConsensusHash, 2)
DEFINE_UINT256_FIELD(sfCheckID, 2)
DEFINE_UINT256_FIELD(sfValidatedHash, 2)
DEFINE_UINT256_FIELD(sfPreviousPageMin, 2)
DEFINE_UINT256_FIELD(sfNextPageMin, 2)
DEFINE_UINT256_FIELD(sfNFTokenBuyOffer, 2)
DEFINE_UINT256_FIELD(sfNFTokenSellOffer, 2)
DEFINE_UINT256_FIELD(sfHookStateKey, 2)
DEFINE_UINT256_FIELD(sfHookHash, 2)
DEFINE_UINT256_FIELD(sfHookNamespace, 2)
DEFINE_UINT256_FIELD(sfHookSetTxnID, 2)
DEFINE_UINT256_FIELD(sfOfferID, 2)
DEFINE_UINT256_FIELD(sfEscrowID, 2)
DEFINE_UINT256_FIELD(sfURITokenID, 2)
DEFINE_UINT256_FIELD(sfGovernanceFlags, 2)
DEFINE_UINT256_FIELD(sfGovernanceMarks, 2)
DEFINE_UINT256_FIELD(sfEmittedTxnID, 2)

DEFINE_AMOUNT_FIELD(sfAmount, 1)
DEFINE_AMOUNT_FIELD(sfBalance, 1)
DEFINE_AMOUNT_FIELD(sfLimitAmount, 1)
DEFINE_AMOUNT_FIELD(sfTakerPays, 1)
DEFINE_AMOUNT_FIELD(sfTakerGets, 1)
DEFINE_AMOUNT_FIELD(sfLowLimit, 1)
DEFINE_AMOUNT_FIELD(sfHighLimit, 1)
DEFINE_NATIVE_AMOUNT_FIELD(sfFee, 1)
DEFINE_AMOUNT_FIELD(sfSendMax, 1)
DEFINE_AMOUNT_FIELD(sfDeliverMin, 1)
DEFINE_AMOUNT_FIELD(sfMinimumOffer, 2)
DEFINE_AMOUNT_FIELD(sfRippleEscrow, 2)
DEFINE_AMOUNT_FIELD(sfDeliveredAmount, 2)
DEFINE_AMOUNT_FIELD(sfNFTokenBrokerFee, 2)
DEFINE_AMOUNT_FIELD(sfHookCallbackFee, 2)
DEFINE_AMOUNT_FIELD(sfLockedBalance, 2)
DEFINE_AMOUNT_FIELD(sfBaseFeeDrops, 2)
DEFINE_AMOUNT_FIELD(sfReserveBaseDrops, 2)
DEFINE_AMOUNT_FIELD(sfReserveIncrementDrops, 2)

DEFINE_VL_FIELD_1(sfPublicKey, 1, 33)
DEFINE_VL_FIELD_1(sfMessageKey, 1, 33)
DEFINE_VL_FIELD_1(sfSigningPubKey, 1, 33)
// DEFINE_VL_FIELD_1(sfTxnSignature, 1)

#define DEFINE_ONE_URI(idx, type) DEFINE_VL_FIELD_##type(sfURI, 1, idx)
DEFINE_VL_FIELD_INDICEX_256(DEFINE_ONE_URI)
// #define DEFINE_ONE_SIGNATURE(idx, type) \
//   DEFINE_VL_FIELD_##type(sfSignature, 1, idx)
// DEFINE_VL_FIELD_INDICEX_256(DEFINE_ONE_SIGNATURE)
// #define DEFINE_ONE_DOMAIN(idx, type) DEFINE_VL_FIELD_##type(sfDomain, 1, idx)
// DEFINE_VL_FIELD_INDICEX_256(DEFINE_ONE_DOMAIN)
// DEFINE_VL_FIELD_1(sfFundCode, 1)
// DEFINE_VL_FIELD_1(sfRemoveCode, 1)
// DEFINE_VL_FIELD_1(sfExpireCode, 1)
// #define DEFINE_ONE_CREATE_CODE(idx, type) \
//   DEFINE_VL_FIELD_##type(sfCreateCode, 1, idx)
// DEFINE_VL_FIELD_INDICEX_512(DEFINE_ONE_CREATE_CODE)
// #define DEFINE_ONE_MEMO_TYPE(idx, type) \
//   DEFINE_VL_FIELD_##type(sfMemoType, 1, idx)
// DEFINE_VL_FIELD_INDICEX_64(DEFINE_ONE_MEMO_TYPE)
// #define DEFINE_ONE_MEMO_DATA(idx, type) \
//   DEFINE_VL_FIELD_##type(sfMemoData, 1, idx)
// DEFINE_VL_FIELD_INDICEX_512(DEFINE_ONE_MEMO_DATA)
// #define DEFINE_ONE_MEMO_FORMAT(idx, type) \
//   DEFINE_VL_FIELD_##type(sfMemoFormat, 1, idx)
// DEFINE_VL_FIELD_INDICEX_64(DEFINE_ONE_MEMO_FORMAT)
// DEFINE_VL_FIELD_1(sfFulfillment, 2)
// DEFINE_VL_FIELD_1(sfCondition, 2)
// DEFINE_VL_FIELD_1(sfMasterSignature, 2)
// DEFINE_VL_FIELD_1(sfUNLModifyValidator, 2, 33)
// DEFINE_VL_FIELD_1(sfValidatorToDisable, 2, 33)
// DEFINE_VL_FIELD_1(sfValidatorToReEnable, 2, 33)
// #define DEFINE_ONE_HOOK_STATE_DATA(idx, type) \
//   DEFINE_VL_FIELD_##type(sfHookStateData, 1, idx)
// DEFINE_VL_FIELD_INDICEX_256(DEFINE_ONE_HOOK_STATE_DATA)
// // #define DEFINE_ONE_HOOK_RETURN_STRING(idx, type) \
// //   DEFINE_VL_FIELD_##type(sfHookReturnString, 1, idx)
// // DEFINE_VL_FIELD_INDICEX_256(DEFINE_ONE_HOOK_RETURN_STRING)
// #define DEFINE_ONE_HOOK_PARAMETER_NAME(idx, type) \
//   DEFINE_VL_FIELD_##type(sfHookParameterName, 1, idx)
// DEFINE_VL_FIELD_INDICEX_32(DEFINE_ONE_HOOK_PARAMETER_NAME)
// #define DEFINE_ONE_HOOK_PARAMETER_VALUE(idx, type) \
//   DEFINE_VL_FIELD_##type(sfHookParameterValue, 2, idx)
// DEFINE_VL_FIELD_INDICEX_128(DEFINE_ONE_HOOK_PARAMETER_VALUE)
#define DEFINE_ONE_BLOB(idx, type) DEFINE_VL_FIELD_##type(sfBlob, 2, idx)
// shoud be 128* 1024
DEFINE_VL_FIELD_INDICEX_512(DEFINE_ONE_BLOB)

DEFINE_ACCOUNT_FIELD(sfAccount, 1)
DEFINE_ACCOUNT_FIELD(sfOwner, 1)
DEFINE_ACCOUNT_FIELD(sfDestination, 1)
DEFINE_ACCOUNT_FIELD(sfIssuer, 1)
DEFINE_ACCOUNT_FIELD(sfAuthorize, 1)
DEFINE_ACCOUNT_FIELD(sfUnauthorize, 1)
DEFINE_ACCOUNT_FIELD(sfRegularKey, 1)
DEFINE_ACCOUNT_FIELD(sfNFTokenMinter, 1)
DEFINE_ACCOUNT_FIELD(sfEmitCallback, 1)
DEFINE_ACCOUNT_FIELD(sfHookAccount, 2)
DEFINE_ACCOUNT_FIELD(sfInform, 2)

DEFINE_VECTOR256_FIELD_1(sfIndexes, 1, 1)
DEFINE_VECTOR256_FIELD_1(sfHashes, 1, 1)
DEFINE_VECTOR256_FIELD_1(sfAmendments, 1, 1)
DEFINE_VECTOR256_FIELD_1(sfNFTokenOffers, 1, 1)
DEFINE_VECTOR256_FIELD_1(sfHookNamespaces, 1, 1)

DEFINE_VECTOR256_FIELD_1(sfURITokenIDs, 2, 1)
DEFINE_VECTOR256_FIELD_1(sfURITokenIDs, 2, 2)
DEFINE_VECTOR256_FIELD_1(sfURITokenIDs, 2, 3)
DEFINE_VECTOR256_FIELD_1(sfURITokenIDs, 2, 4)
DEFINE_VECTOR256_FIELD_1(sfURITokenIDs, 2, 5)
DEFINE_VECTOR256_FIELD_1(sfURITokenIDs, 2, 6)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 7)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 8)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 9)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 10)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 11)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 12)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 13)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 14)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 15)
DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, 16)

// #define DEFINE_ONE_URI_TOKEN_IDS(idx)                                          \
//   DEFINE_VECTOR256_FIELD_2(sfURITokenIDs, 2, idx)
// DEFINE_MULTIPLE_FIELD_INDICEX_16(DEFINE_ONE_URI_TOKEN_IDS)

DEFINE_PATHSET_FIELD(sfPaths, 1)

// DEFINE_OBJECT_FIELD(sfTransactionMetaData, 1)
// DEFINE_OBJECT_FIELD(sfCreatedNode, 1)
// DEFINE_OBJECT_FIELD(sfDeletedNode, 1)
// DEFINE_OBJECT_FIELD(sfModifiedNode, 1)
// DEFINE_OBJECT_FIELD(sfPreviousFields, 1)
// DEFINE_OBJECT_FIELD(sfFinalFields, 1)
// DEFINE_OBJECT_FIELD(sfNewFields, 1)
// DEFINE_OBJECT_FIELD(sfTemplateEntry, 1)
DEFINE_OBJECT_FIELD(
    sfMemo, 1,
    struct Memo {
      OptionalTemplateField<sfMemoType> MemoType;
      TemplateField<sfMemoData> MemoData;
      OptionalTemplateField<sfMemoFormat> MemoFormat;
    },
    Memo)
DEFINE_OPTIONAL_OBJECT_FIELD(
    sfMemo, 1,
    struct Memo {
      OptionalTemplateField<sfMemoType> MemoType;
      OptionalTemplateField<sfMemoData> MemoData;
      OptionalTemplateField<sfMemoFormat> MemoFormat;
    },
    Memo)
DEFINE_OBJECT_FIELD(
    sfSignerEntry, 1,
    struct SignerEntry {
      TemplateField<sfAccount> Account;
      TemplateField<sfSignerWeight> SignerWeight;
      OptionalTemplateField<sfWalletLocator> WalletLocator;
    },
    SignerEntry)
DEFINE_OPTIONAL_OBJECT_FIELD(
    sfSignerEntry, 1,
    struct SignerEntry {
      OptionalTemplateField<sfAccount> Account;
      OptionalTemplateField<sfSignerWeight> SignerWeight;
      OptionalTemplateField<sfWalletLocator> WalletLocator;
    },
    SignerEntry)
// DEFINE_OBJECT_FIELD(sfNFToken, 1)
// DEFINE_OBJECT_FIELD(sfEmitDetails, 1)
// DEFINE_OBJECT_FIELD(sfHook, 1)
// DEFINE_OBJECT_FIELD(sfSigner, 2)
// DEFINE_OBJECT_FIELD(sfMajority, 2)
// DEFINE_OBJECT_FIELD(sfDisabledValidator, 2)
// DEFINE_OBJECT_FIELD(sfEmittedTxn, 2)
// DEFINE_OBJECT_FIELD(sfHookExecution, 2)
// DEFINE_OBJECT_FIELD(sfHookDefinition, 2)
DEFINE_OBJECT_FIELD(
    sfHookParameter, 2,
    struct HookParameter {
      TemplateField<sfHookParameterName> HookParameterName;
      TemplateField<sfHookParameterValue> HookParameterValue;
    },
    HookParameter)
DEFINE_OPTIONAL_OBJECT_FIELD(
    sfHookParameter, 2,
    struct HookParameter {
      OptionalTemplateField<sfHookParameterName> HookParameterName;
      OptionalTemplateField<sfHookParameterValue> HookParameterValue;
    },
    HookParameter)
// DEFINE_OBJECT_FIELD(sfHookGrant, 2)
// DEFINE_OBJECT_FIELD(sfGenesisMint, 2)
// DEFINE_OBJECT_FIELD(sfActiveValidator, 2)
// DEFINE_OBJECT_FIELD(sfImportVLKey, 2)
// DEFINE_OBJECT_FIELD(sfHookEmission, 2)
DEFINE_OBJECT_FIELD(
    sfMintURIToken, 2,
    struct MintURIToken {
      OptionalTemplateField<sfDigest> Digest;
      OptionalTemplateField<sfFlags> Flags;
      TemplateField<sfURI> URI;
    },
    MintURIToken)
DEFINE_OPTIONAL_OBJECT_FIELD(
    sfMintURIToken, 2,
    struct MintURIToken {
      OptionalTemplateField<sfDigest> Digest;
      OptionalTemplateField<sfFlags> Flags;
      OptionalTemplateField<sfURI> URI;
    },
    MintURIToken)

DEFINE_OBJECT_FIELD(
    sfAmountEntry, 2, struct AmountEntry { TemplateField<sfAmount> Amount; },
    AmountEntry)
DEFINE_OPTIONAL_OBJECT_FIELD(
    sfAmountEntry, 2,
    struct OptionalAmountEntry { OptionalTemplateField<sfAmount> Amount; },
    AmountEntry)

#define DEFINE_ONE_SIGNERS(idx) DEFINE_ARRAY_FIELD(sfSigners, 1, sfSigner, idx)
DEFINE_MULTIPLE_FIELD_INDICEX_32(DEFINE_ONE_SIGNERS)
#define DEFINE_ONE_SIGNER_ENTRIES(idx)                                         \
  DEFINE_ARRAY_FIELD(sfSignerEntries, 1, sfSignerEntry, idx)
DEFINE_MULTIPLE_FIELD_INDICEX_32(DEFINE_ONE_SIGNER_ENTRIES)
DEFINE_ARRAY_FIELD(sfTemplate, 1, sfTemplateEntry, 1)
// DEFINE_ARRAY_FIELD(sfNecessary, 1)
// DEFINE_ARRAY_FIELD(sfSufficient, 1)
// for sfModifiedNode, sfCreatedNode, sfDeletedNode
// DEFINE_ARRAY_FIELD(sfAffectedNodes, 1)
#define DEFINE_ONE_MEMOS(idx) DEFINE_ARRAY_FIELD(sfMemos, 1, sfMemo, idx)
DEFINE_MULTIPLE_FIELD_INDICEX_16(DEFINE_ONE_MEMOS)
// #define DEFINE_ONE_NFTOKENS(idx)                                               \
//   DEFINE_ARRAY_FIELD(sfNFTokens, 1, sfNFToken, idx)
// DEFINE_MULTIPLE_FIELD_INDICEX_32(DEFINE_ONE_NFTOKENS)
#define DEFINE_ONE_HOOKS(idx) DEFINE_ARRAY_FIELD(sfHooks, 1, sfHook, idx)
DEFINE_MULTIPLE_FIELD_INDICEX_10(DEFINE_ONE_HOOKS)
// #define DEFINE_ONE_MAJORITIES(idx)                                             \
//   DEFINE_ARRAY_FIELD(sfMajorities, 2, sfMajority, idx)
// DEFINE_MULTIPLE_FIELD_INDICEX_32(DEFINE_ONE_MAJORITIES)
// #define DEFINE_ONE_DISABLED_VALIDATORS(idx) \
//   DEFINE_ARRAY_FIELD(sfDisabledValidators, 2, sfDisabledValidator, idx)
// DEFINE_MULTIPLE_FIELD_INDICEX_32(DEFINE_ONE_DISABLED_VALIDATORS)
#define DEFINE_ONE_HOOK_EXECUTIONS(idx)                                        \
  DEFINE_ARRAY_FIELD(sfHookExecutions, 2, sfHookExecution, idx)
DEFINE_MULTIPLE_FIELD_INDICEX_64(DEFINE_ONE_HOOK_EXECUTIONS)
#define DEFINE_ONE_HOOK_PARAMETERS(idx)                                        \
  DEFINE_ARRAY_FIELD(sfHookParameters, 2, sfHookParameter, idx)
DEFINE_MULTIPLE_FIELD_INDICEX_16(DEFINE_ONE_HOOK_PARAMETERS)
#define DEFINE_ONE_HOOK_GRANTS(idx)                                            \
  DEFINE_ARRAY_FIELD(sfHookGrants, 2, sfHookGrant, idx)
DEFINE_MULTIPLE_FIELD_INDICEX_8(DEFINE_ONE_HOOK_GRANTS)
// #define DEFINE_ONE_GENESIS_MINTS(idx)                                          \
//   DEFINE_ARRAY_FIELD(sfGenesisMints, 2, sfGenesisMint, idx)
// MAX: 512
// DEFINE_MULTIPLE_FIELD_INDICEX_64(DEFINE_ONE_GENESIS_MINTS)
// #define DEFINE_ONE_ACTIVE_VALIDATORS(idx) \
//   DEFINE_ARRAY_FIELD(sfActiveValidators, 2, sfActiveValidator, idx)
// DEFINE_MULTIPLE_FIELD_INDICEX_32(DEFINE_ONE_ACTIVE_VALIDATORS)
// #define DEFINE_ONE_IMPORT_VL_KEYS(idx) \
//   DEFINE_ARRAY_FIELD(sfImportVLKeys, 2, sfImportVLKey, idx)
// DEFINE_MULTIPLE_FIELD_INDICEX_16(DEFINE_ONE_IMPORT_VL_KEYS)
#define DEFINE_ONE_HOOK_EMISSIONS(idx)                                         \
  DEFINE_ARRAY_FIELD(sfHookEmissions, 2, sfHookEmission, idx)
DEFINE_MULTIPLE_FIELD_INDICEX_32(DEFINE_ONE_HOOK_EMISSIONS)
#define DEFINE_ONE_AMOUNTS(idx)                                                \
  DEFINE_ARRAY_FIELD(sfAmounts, 2, sfAmountEntry, idx)
DEFINE_MULTIPLE_FIELD_INDICEX_32(DEFINE_ONE_AMOUNTS)

struct TransactionTemplateBase {
  // Field<sfTransactionType> TransactionType; specify in each template
  TemplateField<sfFlags> Flags;
  TemplateField<sfSequence> Sequence;
  TemplateField<sfFirstLedgerSequence> FirstLedgerSequence;
  TemplateField<sfLastLedgerSequence> LastLedgerSequence;
  TemplateField<sfFee> Fee;
  TemplateField<sfSigningPubKey> SigningPubKey;
  TemplateField<sfAccount> Account;
  OptionalTemplateField<sfEmitDetails> EmitDetails;

  template <typename TemplateType> inline void autofill(TemplateType *txn) {
    // TXN PREPARE: FirstLedgerSequence
    uint32_t fls = (uint32_t)ledger_seq() + 1;
    txn->FirstLedgerSequence.setUint32(fls);

    // TXN PREPARE: LastLedgerSequense
    uint32_t lls = fls + 4;
    txn->LastLedgerSequence.setUint32(lls);

    // TXN PREPARE: Emit Metadata
    etxn_details(uint32_t(&txn->EmitDetails), 116U);

    // TXN PREPARE: Fee
    {
      int64_t fee = etxn_fee_base(uint32_t(txn), sizeof(*txn));
      txn->Fee.setDrops(fee);
    }
  }
};

struct PaymentTemplate : TransactionTemplateBase {
  TemplateField<sfTransactionType> TransactionType = {
      .value = {0x00, ttPAYMENT}};
  TemplateField<sfDestination> Destination;
  TemplateField<sfAmount> Amount;
  inline void autofill() {
    TransactionTemplateBase::autofill<PaymentTemplate>(this);
  }
};

struct AccountSetTemplate : TransactionTemplateBase {
  TemplateField<sfTransactionType> TransactionType = {
      .value = {0x00, ttACCOUNT_SET}};
  inline void autofill() {
    TransactionTemplateBase::autofill<AccountSetTemplate>(this);
  }
};

struct InvokeTemplate : TransactionTemplateBase {
  TemplateField<sfTransactionType> TransactionType = {
      .value = {0x00, ttINVOKE}};
  OptionalTemplateField<sfDestination> Destination;
  inline void autofill() {
    TransactionTemplateBase::autofill<InvokeTemplate>(this);
  }
};

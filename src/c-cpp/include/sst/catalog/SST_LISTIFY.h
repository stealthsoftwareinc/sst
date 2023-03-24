/*
 * Copyright (C) 2012-2023 Stealth Software Technologies, Inc.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice (including
 * the next paragraph) shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef SST_CATALOG_SST_LISTIFY_H
#define SST_CATALOG_SST_LISTIFY_H

#include <sst/catalog/SST_DISPATCH.h>
#include <sst/catalog/SST_EXPAND.h>

#define SST_LISTIFY_2(P, S)

#define SST_LISTIFY_3(P, S, X) P##X

#define SST_LISTIFY_4(P, S, X, ...)                                    \
  P##X SST_EXPAND S SST_LISTIFY_3(P, S, __VA_ARGS__)

#define SST_LISTIFY_5(P, S, X, ...)                                    \
  P##X SST_EXPAND S SST_LISTIFY_4(P, S, __VA_ARGS__)

#define SST_LISTIFY_6(P, S, X, ...)                                    \
  P##X SST_EXPAND S SST_LISTIFY_5(P, S, __VA_ARGS__)

#define SST_LISTIFY_7(P, S, X, ...)                                    \
  P##X SST_EXPAND S SST_LISTIFY_6(P, S, __VA_ARGS__)

#define SST_LISTIFY_8(P, S, X, ...)                                    \
  P##X SST_EXPAND S SST_LISTIFY_7(P, S, __VA_ARGS__)

#define SST_LISTIFY_9(P, S, X, ...)                                    \
  P##X SST_EXPAND S SST_LISTIFY_8(P, S, __VA_ARGS__)

#define SST_LISTIFY_10(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_9(P, S, __VA_ARGS__)

#define SST_LISTIFY_11(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_10(P, S, __VA_ARGS__)

#define SST_LISTIFY_12(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_11(P, S, __VA_ARGS__)

#define SST_LISTIFY_13(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_12(P, S, __VA_ARGS__)

#define SST_LISTIFY_14(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_13(P, S, __VA_ARGS__)

#define SST_LISTIFY_15(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_14(P, S, __VA_ARGS__)

#define SST_LISTIFY_16(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_15(P, S, __VA_ARGS__)

#define SST_LISTIFY_17(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_16(P, S, __VA_ARGS__)

#define SST_LISTIFY_18(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_17(P, S, __VA_ARGS__)

#define SST_LISTIFY_19(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_18(P, S, __VA_ARGS__)

#define SST_LISTIFY_20(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_19(P, S, __VA_ARGS__)

#define SST_LISTIFY_21(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_20(P, S, __VA_ARGS__)

#define SST_LISTIFY_22(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_21(P, S, __VA_ARGS__)

#define SST_LISTIFY_23(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_22(P, S, __VA_ARGS__)

#define SST_LISTIFY_24(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_23(P, S, __VA_ARGS__)

#define SST_LISTIFY_25(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_24(P, S, __VA_ARGS__)

#define SST_LISTIFY_26(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_25(P, S, __VA_ARGS__)

#define SST_LISTIFY_27(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_26(P, S, __VA_ARGS__)

#define SST_LISTIFY_28(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_27(P, S, __VA_ARGS__)

#define SST_LISTIFY_29(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_28(P, S, __VA_ARGS__)

#define SST_LISTIFY_30(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_29(P, S, __VA_ARGS__)

#define SST_LISTIFY_31(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_30(P, S, __VA_ARGS__)

#define SST_LISTIFY_32(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_31(P, S, __VA_ARGS__)

#define SST_LISTIFY_33(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_32(P, S, __VA_ARGS__)

#define SST_LISTIFY_34(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_33(P, S, __VA_ARGS__)

#define SST_LISTIFY_35(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_34(P, S, __VA_ARGS__)

#define SST_LISTIFY_36(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_35(P, S, __VA_ARGS__)

#define SST_LISTIFY_37(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_36(P, S, __VA_ARGS__)

#define SST_LISTIFY_38(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_37(P, S, __VA_ARGS__)

#define SST_LISTIFY_39(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_38(P, S, __VA_ARGS__)

#define SST_LISTIFY_40(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_39(P, S, __VA_ARGS__)

#define SST_LISTIFY_41(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_40(P, S, __VA_ARGS__)

#define SST_LISTIFY_42(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_41(P, S, __VA_ARGS__)

#define SST_LISTIFY_43(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_42(P, S, __VA_ARGS__)

#define SST_LISTIFY_44(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_43(P, S, __VA_ARGS__)

#define SST_LISTIFY_45(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_44(P, S, __VA_ARGS__)

#define SST_LISTIFY_46(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_45(P, S, __VA_ARGS__)

#define SST_LISTIFY_47(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_46(P, S, __VA_ARGS__)

#define SST_LISTIFY_48(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_47(P, S, __VA_ARGS__)

#define SST_LISTIFY_49(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_48(P, S, __VA_ARGS__)

#define SST_LISTIFY_50(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_49(P, S, __VA_ARGS__)

#define SST_LISTIFY_51(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_50(P, S, __VA_ARGS__)

#define SST_LISTIFY_52(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_51(P, S, __VA_ARGS__)

#define SST_LISTIFY_53(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_52(P, S, __VA_ARGS__)

#define SST_LISTIFY_54(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_53(P, S, __VA_ARGS__)

#define SST_LISTIFY_55(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_54(P, S, __VA_ARGS__)

#define SST_LISTIFY_56(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_55(P, S, __VA_ARGS__)

#define SST_LISTIFY_57(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_56(P, S, __VA_ARGS__)

#define SST_LISTIFY_58(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_57(P, S, __VA_ARGS__)

#define SST_LISTIFY_59(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_58(P, S, __VA_ARGS__)

#define SST_LISTIFY_60(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_59(P, S, __VA_ARGS__)

#define SST_LISTIFY_61(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_60(P, S, __VA_ARGS__)

#define SST_LISTIFY_62(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_61(P, S, __VA_ARGS__)

#define SST_LISTIFY_63(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_62(P, S, __VA_ARGS__)

#define SST_LISTIFY_64(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_63(P, S, __VA_ARGS__)

#define SST_LISTIFY_65(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_64(P, S, __VA_ARGS__)

#define SST_LISTIFY_66(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_65(P, S, __VA_ARGS__)

#define SST_LISTIFY_67(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_66(P, S, __VA_ARGS__)

#define SST_LISTIFY_68(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_67(P, S, __VA_ARGS__)

#define SST_LISTIFY_69(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_68(P, S, __VA_ARGS__)

#define SST_LISTIFY_70(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_69(P, S, __VA_ARGS__)

#define SST_LISTIFY_71(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_70(P, S, __VA_ARGS__)

#define SST_LISTIFY_72(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_71(P, S, __VA_ARGS__)

#define SST_LISTIFY_73(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_72(P, S, __VA_ARGS__)

#define SST_LISTIFY_74(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_73(P, S, __VA_ARGS__)

#define SST_LISTIFY_75(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_74(P, S, __VA_ARGS__)

#define SST_LISTIFY_76(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_75(P, S, __VA_ARGS__)

#define SST_LISTIFY_77(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_76(P, S, __VA_ARGS__)

#define SST_LISTIFY_78(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_77(P, S, __VA_ARGS__)

#define SST_LISTIFY_79(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_78(P, S, __VA_ARGS__)

#define SST_LISTIFY_80(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_79(P, S, __VA_ARGS__)

#define SST_LISTIFY_81(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_80(P, S, __VA_ARGS__)

#define SST_LISTIFY_82(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_81(P, S, __VA_ARGS__)

#define SST_LISTIFY_83(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_82(P, S, __VA_ARGS__)

#define SST_LISTIFY_84(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_83(P, S, __VA_ARGS__)

#define SST_LISTIFY_85(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_84(P, S, __VA_ARGS__)

#define SST_LISTIFY_86(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_85(P, S, __VA_ARGS__)

#define SST_LISTIFY_87(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_86(P, S, __VA_ARGS__)

#define SST_LISTIFY_88(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_87(P, S, __VA_ARGS__)

#define SST_LISTIFY_89(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_88(P, S, __VA_ARGS__)

#define SST_LISTIFY_90(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_89(P, S, __VA_ARGS__)

#define SST_LISTIFY_91(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_90(P, S, __VA_ARGS__)

#define SST_LISTIFY_92(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_91(P, S, __VA_ARGS__)

#define SST_LISTIFY_93(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_92(P, S, __VA_ARGS__)

#define SST_LISTIFY_94(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_93(P, S, __VA_ARGS__)

#define SST_LISTIFY_95(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_94(P, S, __VA_ARGS__)

#define SST_LISTIFY_96(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_95(P, S, __VA_ARGS__)

#define SST_LISTIFY_97(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_96(P, S, __VA_ARGS__)

#define SST_LISTIFY_98(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_97(P, S, __VA_ARGS__)

#define SST_LISTIFY_99(P, S, X, ...)                                   \
  P##X SST_EXPAND S SST_LISTIFY_98(P, S, __VA_ARGS__)

#define SST_LISTIFY_100(P, S, X, ...)                                  \
  P##X SST_EXPAND S SST_LISTIFY_99(P, S, __VA_ARGS__)

#define SST_LISTIFY(...)                                               \
  SST_DISPATCH(SST_LISTIFY_, __VA_ARGS__)(__VA_ARGS__)

#endif // #ifndef SST_CATALOG_SST_LISTIFY_H

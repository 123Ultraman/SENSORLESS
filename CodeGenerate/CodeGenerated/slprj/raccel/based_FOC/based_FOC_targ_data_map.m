    function targMap = targDataMap(),

    ;%***********************
    ;% Create Parameter Map *
    ;%***********************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 4;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc paramMap
        ;%
        paramMap.nSections           = nTotSects;
        paramMap.sectIdxOffset       = sectIdxOffset;
            paramMap.sections(nTotSects) = dumSection; %prealloc
        paramMap.nTotData            = -1;

        ;%
        ;% Auto data (rtP)
        ;%
            section.nData     = 11;
            section.data(11)  = dumData; %prealloc

                    ;% rtP.F1
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.U_ref
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 500;

                    ;% rtP._L2f2Based_FOC_Data_sldd_
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 1000;

                    ;% rtP._PLL_I2f2Based_FOC_Data_sldd_
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 1001;

                    ;% rtP._PLL_P2f2Based_FOC_Data_sldd_
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 1002;

                    ;% rtP._Period2f2Based_FOC_Data_sldd_
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 1003;

                    ;% rtP._Pn2f2Based_FOC_Data_sldd_
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 1004;

                    ;% rtP._Rs2f2Based_FOC_Data_sldd_
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 1005;

                    ;% rtP._Ts2f2Based_FOC_Data_sldd_
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 1006;

                    ;% rtP._Udc2f2Based_FOC_Data_sldd_
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 1007;

                    ;% rtP._flux2f2Based_FOC_Data_sldd_
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 1008;

            nTotData = nTotData + section.nData;
            paramMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtP._gamma2f2Based_FOC_Data_sldd_
                    section.data(1).logicalSrcIdx = 11;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            paramMap.sections(2) = section;
            clear section

            section.nData     = 141;
            section.data(141)  = dumData; %prealloc

                    ;% rtP.DCVoltageSource1_Amplitude
                    section.data(1).logicalSrcIdx = 12;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.LowPassFilterDiscreteorContinuous_K
                    section.data(2).logicalSrcIdx = 13;
                    section.data(2).dtTransOffset = 1;

                    ;% rtP.Subsystem3_Kd
                    section.data(3).logicalSrcIdx = 14;
                    section.data(3).dtTransOffset = 2;

                    ;% rtP.Subsystem_Kd
                    section.data(4).logicalSrcIdx = 15;
                    section.data(4).dtTransOffset = 3;

                    ;% rtP.Subsystem2_Kd
                    section.data(5).logicalSrcIdx = 16;
                    section.data(5).dtTransOffset = 4;

                    ;% rtP.Subsystem3_Kd_nwkkd3n4ya
                    section.data(6).logicalSrcIdx = 17;
                    section.data(6).dtTransOffset = 5;

                    ;% rtP.Subsystem_Ki
                    section.data(7).logicalSrcIdx = 18;
                    section.data(7).dtTransOffset = 6;

                    ;% rtP.Subsystem2_Ki
                    section.data(8).logicalSrcIdx = 19;
                    section.data(8).dtTransOffset = 7;

                    ;% rtP.Subsystem3_Ki
                    section.data(9).logicalSrcIdx = 20;
                    section.data(9).dtTransOffset = 8;

                    ;% rtP.Subsystem_Kp
                    section.data(10).logicalSrcIdx = 21;
                    section.data(10).dtTransOffset = 9;

                    ;% rtP.Subsystem2_Kp
                    section.data(11).logicalSrcIdx = 22;
                    section.data(11).dtTransOffset = 10;

                    ;% rtP.Subsystem3_Kp
                    section.data(12).logicalSrcIdx = 23;
                    section.data(12).dtTransOffset = 11;

                    ;% rtP.LowPassFilterDiscreteorContinuous_T
                    section.data(13).logicalSrcIdx = 24;
                    section.data(13).dtTransOffset = 12;

                    ;% rtP.Subsystem3_Ts
                    section.data(14).logicalSrcIdx = 25;
                    section.data(14).dtTransOffset = 13;

                    ;% rtP.Subsystem_Ts
                    section.data(15).logicalSrcIdx = 26;
                    section.data(15).dtTransOffset = 14;

                    ;% rtP.Subsystem2_Ts
                    section.data(16).logicalSrcIdx = 27;
                    section.data(16).dtTransOffset = 15;

                    ;% rtP.Subsystem3_Ts_gafktesne5
                    section.data(17).logicalSrcIdx = 28;
                    section.data(17).dtTransOffset = 16;

                    ;% rtP.CompareToConstant_const
                    section.data(18).logicalSrcIdx = 29;
                    section.data(18).dtTransOffset = 17;

                    ;% rtP.CompareToConstant_const_fh44bbmvpu
                    section.data(19).logicalSrcIdx = 30;
                    section.data(19).dtTransOffset = 18;

                    ;% rtP.CoulombViscousFriction_gain
                    section.data(20).logicalSrcIdx = 31;
                    section.data(20).dtTransOffset = 19;

                    ;% rtP.LowPassFilterDiscreteorContinuous_init_option
                    section.data(21).logicalSrcIdx = 32;
                    section.data(21).dtTransOffset = 20;

                    ;% rtP.Subsystem3_max_Integral
                    section.data(22).logicalSrcIdx = 33;
                    section.data(22).dtTransOffset = 21;

                    ;% rtP.Subsystem_max_Integral
                    section.data(23).logicalSrcIdx = 34;
                    section.data(23).dtTransOffset = 22;

                    ;% rtP.Subsystem2_max_Integral
                    section.data(24).logicalSrcIdx = 35;
                    section.data(24).dtTransOffset = 23;

                    ;% rtP.Subsystem3_max_Integral_pc1i5p255z
                    section.data(25).logicalSrcIdx = 36;
                    section.data(25).dtTransOffset = 24;

                    ;% rtP.Subsystem3_max_output
                    section.data(26).logicalSrcIdx = 37;
                    section.data(26).dtTransOffset = 25;

                    ;% rtP.Subsystem_max_output
                    section.data(27).logicalSrcIdx = 38;
                    section.data(27).dtTransOffset = 26;

                    ;% rtP.Subsystem2_max_output
                    section.data(28).logicalSrcIdx = 39;
                    section.data(28).dtTransOffset = 27;

                    ;% rtP.Subsystem3_max_output_fnwgdzd14e
                    section.data(29).logicalSrcIdx = 40;
                    section.data(29).dtTransOffset = 28;

                    ;% rtP.Subsystem3_min_Integral
                    section.data(30).logicalSrcIdx = 41;
                    section.data(30).dtTransOffset = 29;

                    ;% rtP.Subsystem_min_Integral
                    section.data(31).logicalSrcIdx = 42;
                    section.data(31).dtTransOffset = 30;

                    ;% rtP.Subsystem2_min_Integral
                    section.data(32).logicalSrcIdx = 43;
                    section.data(32).dtTransOffset = 31;

                    ;% rtP.Subsystem3_min_Integral_bhno53osaw
                    section.data(33).logicalSrcIdx = 44;
                    section.data(33).dtTransOffset = 32;

                    ;% rtP.Subsystem3_min_output
                    section.data(34).logicalSrcIdx = 45;
                    section.data(34).dtTransOffset = 33;

                    ;% rtP.Subsystem_min_output
                    section.data(35).logicalSrcIdx = 46;
                    section.data(35).dtTransOffset = 34;

                    ;% rtP.Subsystem2_min_output
                    section.data(36).logicalSrcIdx = 47;
                    section.data(36).dtTransOffset = 35;

                    ;% rtP.Subsystem3_min_output_k03ehr1wvd
                    section.data(37).logicalSrcIdx = 48;
                    section.data(37).dtTransOffset = 36;

                    ;% rtP.CoulombViscousFriction_offset
                    section.data(38).logicalSrcIdx = 49;
                    section.data(38).dtTransOffset = 37;

                    ;% rtP.RepeatingSequence1_rep_seq_y
                    section.data(39).logicalSrcIdx = 50;
                    section.data(39).dtTransOffset = 38;

                    ;% rtP.Constant_Value
                    section.data(40).logicalSrcIdx = 51;
                    section.data(40).dtTransOffset = 41;

                    ;% rtP.Delay_InitialCondition
                    section.data(41).logicalSrcIdx = 52;
                    section.data(41).dtTransOffset = 42;

                    ;% rtP.Delay1_InitialCondition
                    section.data(42).logicalSrcIdx = 53;
                    section.data(42).dtTransOffset = 43;

                    ;% rtP.DiscreteTimeIntegrator_gainval
                    section.data(43).logicalSrcIdx = 54;
                    section.data(43).dtTransOffset = 44;

                    ;% rtP.DiscreteTimeIntegrator_IC
                    section.data(44).logicalSrcIdx = 55;
                    section.data(44).dtTransOffset = 45;

                    ;% rtP.Integrator_gainval
                    section.data(45).logicalSrcIdx = 56;
                    section.data(45).dtTransOffset = 46;

                    ;% rtP.Integrator_UpperSat
                    section.data(46).logicalSrcIdx = 57;
                    section.data(46).dtTransOffset = 47;

                    ;% rtP.Integrator_LowerSat
                    section.data(47).logicalSrcIdx = 58;
                    section.data(47).dtTransOffset = 48;

                    ;% rtP.Saturation_UpperSat
                    section.data(48).logicalSrcIdx = 59;
                    section.data(48).dtTransOffset = 49;

                    ;% rtP.Saturation_LowerSat
                    section.data(49).logicalSrcIdx = 60;
                    section.data(49).dtTransOffset = 50;

                    ;% rtP.Constant3_Value
                    section.data(50).logicalSrcIdx = 61;
                    section.data(50).dtTransOffset = 51;

                    ;% rtP.Tcm1_Y0
                    section.data(51).logicalSrcIdx = 62;
                    section.data(51).dtTransOffset = 52;

                    ;% rtP.Tcm2_Y0
                    section.data(52).logicalSrcIdx = 63;
                    section.data(52).dtTransOffset = 53;

                    ;% rtP.Tcm3_Y0
                    section.data(53).logicalSrcIdx = 64;
                    section.data(53).dtTransOffset = 54;

                    ;% rtP.Delay1_InitialCondition_d0okqqbyaz
                    section.data(54).logicalSrcIdx = 65;
                    section.data(54).dtTransOffset = 55;

                    ;% rtP.Delay_InitialCondition_b1lbjxwxpj
                    section.data(55).logicalSrcIdx = 66;
                    section.data(55).dtTransOffset = 56;

                    ;% rtP.Gain1_Gain
                    section.data(56).logicalSrcIdx = 67;
                    section.data(56).dtTransOffset = 57;

                    ;% rtP.Constant_Value_eugrpqijcm
                    section.data(57).logicalSrcIdx = 68;
                    section.data(57).dtTransOffset = 58;

                    ;% rtP.Id_ref_Value
                    section.data(58).logicalSrcIdx = 69;
                    section.data(58).dtTransOffset = 59;

                    ;% rtP.Gain_Gain
                    section.data(59).logicalSrcIdx = 70;
                    section.data(59).dtTransOffset = 60;

                    ;% rtP.Gain_Gain_mk3bjbwrde
                    section.data(60).logicalSrcIdx = 71;
                    section.data(60).dtTransOffset = 61;

                    ;% rtP.Gain_Gain_oivnklv25u
                    section.data(61).logicalSrcIdx = 72;
                    section.data(61).dtTransOffset = 62;

                    ;% rtP.Gain_Gain_cnjrb05lj0
                    section.data(62).logicalSrcIdx = 73;
                    section.data(62).dtTransOffset = 63;

                    ;% rtP.Gain_Gain_g1t15nmsmn
                    section.data(63).logicalSrcIdx = 74;
                    section.data(63).dtTransOffset = 64;

                    ;% rtP.Gain_Gain_bzsgmuimqy
                    section.data(64).logicalSrcIdx = 75;
                    section.data(64).dtTransOffset = 65;

                    ;% rtP.DiscreteTimeIntegrator1_gainval
                    section.data(65).logicalSrcIdx = 76;
                    section.data(65).dtTransOffset = 66;

                    ;% rtP.DiscreteTimeIntegrator1_IC
                    section.data(66).logicalSrcIdx = 77;
                    section.data(66).dtTransOffset = 67;

                    ;% rtP.DiscreteTimeIntegrator_gainval_paiswrmeqy
                    section.data(67).logicalSrcIdx = 78;
                    section.data(67).dtTransOffset = 68;

                    ;% rtP.DiscreteTimeIntegrator_IC_mu4lei3aeq
                    section.data(68).logicalSrcIdx = 79;
                    section.data(68).dtTransOffset = 69;

                    ;% rtP.DiscreteTimeIntegrator_gainval_l5nc5jul3w
                    section.data(69).logicalSrcIdx = 80;
                    section.data(69).dtTransOffset = 70;

                    ;% rtP.DiscreteTimeIntegrator_IC_jlygup22ed
                    section.data(70).logicalSrcIdx = 81;
                    section.data(70).dtTransOffset = 71;

                    ;% rtP.DiscreteTimeIntegrator_gainval_ezgr3u4l02
                    section.data(71).logicalSrcIdx = 82;
                    section.data(71).dtTransOffset = 72;

                    ;% rtP.DiscreteTimeIntegrator_IC_nkd2pr4ny4
                    section.data(72).logicalSrcIdx = 83;
                    section.data(72).dtTransOffset = 73;

                    ;% rtP.PulseGenerator_Amp
                    section.data(73).logicalSrcIdx = 84;
                    section.data(73).dtTransOffset = 74;

                    ;% rtP.PulseGenerator_Period
                    section.data(74).logicalSrcIdx = 85;
                    section.data(74).dtTransOffset = 75;

                    ;% rtP.PulseGenerator_Duty
                    section.data(75).logicalSrcIdx = 86;
                    section.data(75).dtTransOffset = 76;

                    ;% rtP.PulseGenerator_PhaseDelay
                    section.data(76).logicalSrcIdx = 87;
                    section.data(76).dtTransOffset = 77;

                    ;% rtP.LookUpTable1_bp01Data
                    section.data(77).logicalSrcIdx = 88;
                    section.data(77).dtTransOffset = 78;

                    ;% rtP.Relay_OnVal
                    section.data(78).logicalSrcIdx = 89;
                    section.data(78).dtTransOffset = 81;

                    ;% rtP.Relay_OffVal
                    section.data(79).logicalSrcIdx = 90;
                    section.data(79).dtTransOffset = 82;

                    ;% rtP.Relay_YOn
                    section.data(80).logicalSrcIdx = 91;
                    section.data(80).dtTransOffset = 83;

                    ;% rtP.Relay_YOff
                    section.data(81).logicalSrcIdx = 92;
                    section.data(81).dtTransOffset = 84;

                    ;% rtP.Relay1_OnVal
                    section.data(82).logicalSrcIdx = 93;
                    section.data(82).dtTransOffset = 85;

                    ;% rtP.Relay1_OffVal
                    section.data(83).logicalSrcIdx = 94;
                    section.data(83).dtTransOffset = 86;

                    ;% rtP.Relay1_YOn
                    section.data(84).logicalSrcIdx = 95;
                    section.data(84).dtTransOffset = 87;

                    ;% rtP.Relay1_YOff
                    section.data(85).logicalSrcIdx = 96;
                    section.data(85).dtTransOffset = 88;

                    ;% rtP.Relay2_OnVal
                    section.data(86).logicalSrcIdx = 97;
                    section.data(86).dtTransOffset = 89;

                    ;% rtP.Relay2_OffVal
                    section.data(87).logicalSrcIdx = 98;
                    section.data(87).dtTransOffset = 90;

                    ;% rtP.Relay2_YOn
                    section.data(88).logicalSrcIdx = 99;
                    section.data(88).dtTransOffset = 91;

                    ;% rtP.Relay2_YOff
                    section.data(89).logicalSrcIdx = 100;
                    section.data(89).dtTransOffset = 92;

                    ;% rtP.Saturation_UpperSat_lvhbmvqtsm
                    section.data(90).logicalSrcIdx = 101;
                    section.data(90).dtTransOffset = 93;

                    ;% rtP.Saturation_LowerSat_mxekufxfq4
                    section.data(91).logicalSrcIdx = 102;
                    section.data(91).dtTransOffset = 94;

                    ;% rtP.UnitDelay5_InitialCondition
                    section.data(92).logicalSrcIdx = 103;
                    section.data(92).dtTransOffset = 95;

                    ;% rtP.Gain4_Gain
                    section.data(93).logicalSrcIdx = 104;
                    section.data(93).dtTransOffset = 96;

                    ;% rtP.UnitDelay6_InitialCondition
                    section.data(94).logicalSrcIdx = 105;
                    section.data(94).dtTransOffset = 97;

                    ;% rtP.UnitDelay1_InitialCondition
                    section.data(95).logicalSrcIdx = 106;
                    section.data(95).dtTransOffset = 98;

                    ;% rtP.StateSpace_DS_param
                    section.data(96).logicalSrcIdx = 107;
                    section.data(96).dtTransOffset = 99;

                    ;% rtP.Switch_Threshold
                    section.data(97).logicalSrcIdx = 108;
                    section.data(97).dtTransOffset = 297;

                    ;% rtP.Saturation_UpperSat_fsy5ziaufk
                    section.data(98).logicalSrcIdx = 109;
                    section.data(98).dtTransOffset = 298;

                    ;% rtP.Saturation_LowerSat_lcctrgol0c
                    section.data(99).logicalSrcIdx = 110;
                    section.data(99).dtTransOffset = 299;

                    ;% rtP.Switch_Threshold_ejumnfp2iv
                    section.data(100).logicalSrcIdx = 111;
                    section.data(100).dtTransOffset = 300;

                    ;% rtP.Saturation_UpperSat_gahcyazdwu
                    section.data(101).logicalSrcIdx = 112;
                    section.data(101).dtTransOffset = 301;

                    ;% rtP.Saturation_LowerSat_omyxtylrr2
                    section.data(102).logicalSrcIdx = 113;
                    section.data(102).dtTransOffset = 302;

                    ;% rtP.Switch_Threshold_ckrsclarb5
                    section.data(103).logicalSrcIdx = 114;
                    section.data(103).dtTransOffset = 303;

                    ;% rtP.Saturation_UpperSat_dzgt10esff
                    section.data(104).logicalSrcIdx = 115;
                    section.data(104).dtTransOffset = 304;

                    ;% rtP.Saturation_LowerSat_fh1umgpwfe
                    section.data(105).logicalSrcIdx = 116;
                    section.data(105).dtTransOffset = 305;

                    ;% rtP.Switch_Threshold_bxqw2aoic5
                    section.data(106).logicalSrcIdx = 117;
                    section.data(106).dtTransOffset = 306;

                    ;% rtP.Saturation_UpperSat_maem4qlhjb
                    section.data(107).logicalSrcIdx = 118;
                    section.data(107).dtTransOffset = 307;

                    ;% rtP.Saturation_LowerSat_bi44mm4520
                    section.data(108).logicalSrcIdx = 119;
                    section.data(108).dtTransOffset = 308;

                    ;% rtP.Switch_Threshold_onyd2dtacm
                    section.data(109).logicalSrcIdx = 120;
                    section.data(109).dtTransOffset = 309;

                    ;% rtP.Saturation_UpperSat_lfg1vg5xfs
                    section.data(110).logicalSrcIdx = 121;
                    section.data(110).dtTransOffset = 310;

                    ;% rtP.Saturation_LowerSat_oaquejrj11
                    section.data(111).logicalSrcIdx = 122;
                    section.data(111).dtTransOffset = 311;

                    ;% rtP.Switch_Threshold_jaxwwid1sf
                    section.data(112).logicalSrcIdx = 123;
                    section.data(112).dtTransOffset = 312;

                    ;% rtP.Saturation_UpperSat_ciqrhxjwb1
                    section.data(113).logicalSrcIdx = 124;
                    section.data(113).dtTransOffset = 313;

                    ;% rtP.Saturation_LowerSat_l5rgpp0wbq
                    section.data(114).logicalSrcIdx = 125;
                    section.data(114).dtTransOffset = 314;

                    ;% rtP.donotdeletethisgain_Gain
                    section.data(115).logicalSrcIdx = 126;
                    section.data(115).dtTransOffset = 315;

                    ;% rtP.uLd_Gain
                    section.data(116).logicalSrcIdx = 127;
                    section.data(116).dtTransOffset = 316;

                    ;% rtP.Gain_Gain_anscm3fjqp
                    section.data(117).logicalSrcIdx = 128;
                    section.data(117).dtTransOffset = 317;

                    ;% rtP.LqLd_Gain
                    section.data(118).logicalSrcIdx = 129;
                    section.data(118).dtTransOffset = 318;

                    ;% rtP.RLd_Gain
                    section.data(119).logicalSrcIdx = 130;
                    section.data(119).dtTransOffset = 319;

                    ;% rtP.uLq_Gain
                    section.data(120).logicalSrcIdx = 131;
                    section.data(120).dtTransOffset = 320;

                    ;% rtP.LdLq_Gain
                    section.data(121).logicalSrcIdx = 132;
                    section.data(121).dtTransOffset = 321;

                    ;% rtP.RLq_Gain
                    section.data(122).logicalSrcIdx = 133;
                    section.data(122).dtTransOffset = 322;

                    ;% rtP.lamLq_Gain
                    section.data(123).logicalSrcIdx = 134;
                    section.data(123).dtTransOffset = 323;

                    ;% rtP.Gain2_Gain
                    section.data(124).logicalSrcIdx = 135;
                    section.data(124).dtTransOffset = 324;

                    ;% rtP.SwitchCurrents_Value
                    section.data(125).logicalSrcIdx = 136;
                    section.data(125).dtTransOffset = 325;

                    ;% rtP.u1_Value
                    section.data(126).logicalSrcIdx = 137;
                    section.data(126).dtTransOffset = 331;

                    ;% rtP.eee_Value
                    section.data(127).logicalSrcIdx = 138;
                    section.data(127).dtTransOffset = 332;

                    ;% rtP.u1_Value_nreyg4opoj
                    section.data(128).logicalSrcIdx = 139;
                    section.data(128).dtTransOffset = 333;

                    ;% rtP.eee_Value_ewdqtje3b0
                    section.data(129).logicalSrcIdx = 140;
                    section.data(129).dtTransOffset = 334;

                    ;% rtP.u1_Value_ls0m5pykfy
                    section.data(130).logicalSrcIdx = 141;
                    section.data(130).dtTransOffset = 335;

                    ;% rtP.eee_Value_h1qjq4lqkf
                    section.data(131).logicalSrcIdx = 142;
                    section.data(131).dtTransOffset = 336;

                    ;% rtP.u1_Value_jwxgunvume
                    section.data(132).logicalSrcIdx = 143;
                    section.data(132).dtTransOffset = 337;

                    ;% rtP.eee_Value_bupr5ec5gd
                    section.data(133).logicalSrcIdx = 144;
                    section.data(133).dtTransOffset = 338;

                    ;% rtP.u1_Value_l2dpiazvzy
                    section.data(134).logicalSrcIdx = 145;
                    section.data(134).dtTransOffset = 339;

                    ;% rtP.eee_Value_g1uo4tygcq
                    section.data(135).logicalSrcIdx = 146;
                    section.data(135).dtTransOffset = 340;

                    ;% rtP.u1_Value_gm2dshzm4f
                    section.data(136).logicalSrcIdx = 147;
                    section.data(136).dtTransOffset = 341;

                    ;% rtP.eee_Value_jnqgmu1ji4
                    section.data(137).logicalSrcIdx = 148;
                    section.data(137).dtTransOffset = 342;

                    ;% rtP.Constant1_Value
                    section.data(138).logicalSrcIdx = 149;
                    section.data(138).dtTransOffset = 343;

                    ;% rtP.Constant8_Value
                    section.data(139).logicalSrcIdx = 150;
                    section.data(139).dtTransOffset = 344;

                    ;% rtP.Constant_Value_geepaef2cb
                    section.data(140).logicalSrcIdx = 151;
                    section.data(140).dtTransOffset = 345;

                    ;% rtP.Constant1_Value_p1uxhfeofi
                    section.data(141).logicalSrcIdx = 152;
                    section.data(141).dtTransOffset = 346;

            nTotData = nTotData + section.nData;
            paramMap.sections(3) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtP.ManualSwitch1_CurrentSetting
                    section.data(1).logicalSrcIdx = 153;
                    section.data(1).dtTransOffset = 0;

                    ;% rtP.ManualSwitch_CurrentSetting
                    section.data(2).logicalSrcIdx = 154;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            paramMap.sections(4) = section;
            clear section


            ;%
            ;% Non-auto Data (parameter)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        paramMap.nTotData = nTotData;



    ;%**************************
    ;% Create Block Output Map *
    ;%**************************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 5;
        sectIdxOffset = 0;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc sigMap
        ;%
        sigMap.nSections           = nTotSects;
        sigMap.sectIdxOffset       = sectIdxOffset;
            sigMap.sections(nTotSects) = dumSection; %prealloc
        sigMap.nTotData            = -1;

        ;%
        ;% Auto data (rtB)
        ;%
            section.nData     = 55;
            section.data(55)  = dumData; %prealloc

                    ;% rtB.bvmgpm2odd
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtB.i411d5wrsj
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% rtB.mxfho1lu3p
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% rtB.ddvi5ihagt
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% rtB.imi2lpdtr1
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% rtB.jtbsnoer54
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% rtB.h4vz5f5kaw
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% rtB.bils2pe3o0
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% rtB.o4d5sop3qe
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% rtB.ed2v4avx3x
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% rtB.ddnhwcdugb
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 10;

                    ;% rtB.iybpytrzjw
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 11;

                    ;% rtB.bbct5xrocn
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 12;

                    ;% rtB.m22zcfn1ms
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 13;

                    ;% rtB.c3zvc1ql15
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 14;

                    ;% rtB.iydpuygsg3
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 15;

                    ;% rtB.cng1w212ln
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 16;

                    ;% rtB.e2oy154v1u
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 17;

                    ;% rtB.ofmh5pmvcs
                    section.data(19).logicalSrcIdx = 18;
                    section.data(19).dtTransOffset = 26;

                    ;% rtB.adfbnhoe4d
                    section.data(20).logicalSrcIdx = 19;
                    section.data(20).dtTransOffset = 32;

                    ;% rtB.kb4r4hmq10
                    section.data(21).logicalSrcIdx = 20;
                    section.data(21).dtTransOffset = 33;

                    ;% rtB.lac35nslzw
                    section.data(22).logicalSrcIdx = 21;
                    section.data(22).dtTransOffset = 34;

                    ;% rtB.ckny4k4ajb
                    section.data(23).logicalSrcIdx = 22;
                    section.data(23).dtTransOffset = 35;

                    ;% rtB.hlxa3tdq2m
                    section.data(24).logicalSrcIdx = 23;
                    section.data(24).dtTransOffset = 36;

                    ;% rtB.bdgz0nrhdj
                    section.data(25).logicalSrcIdx = 24;
                    section.data(25).dtTransOffset = 37;

                    ;% rtB.nq0riy0nl0
                    section.data(26).logicalSrcIdx = 25;
                    section.data(26).dtTransOffset = 38;

                    ;% rtB.h5dgx5wmy1
                    section.data(27).logicalSrcIdx = 26;
                    section.data(27).dtTransOffset = 39;

                    ;% rtB.dvdx0svzcc
                    section.data(28).logicalSrcIdx = 27;
                    section.data(28).dtTransOffset = 40;

                    ;% rtB.g1qadio5dk
                    section.data(29).logicalSrcIdx = 28;
                    section.data(29).dtTransOffset = 41;

                    ;% rtB.f4ynojnm2r
                    section.data(30).logicalSrcIdx = 29;
                    section.data(30).dtTransOffset = 47;

                    ;% rtB.hgeuugh2cl
                    section.data(31).logicalSrcIdx = 30;
                    section.data(31).dtTransOffset = 48;

                    ;% rtB.n0qw4xb12u
                    section.data(32).logicalSrcIdx = 31;
                    section.data(32).dtTransOffset = 49;

                    ;% rtB.ojdhbpltph
                    section.data(33).logicalSrcIdx = 32;
                    section.data(33).dtTransOffset = 50;

                    ;% rtB.klllytdpmn
                    section.data(34).logicalSrcIdx = 33;
                    section.data(34).dtTransOffset = 51;

                    ;% rtB.o3rovp4hg1
                    section.data(35).logicalSrcIdx = 34;
                    section.data(35).dtTransOffset = 52;

                    ;% rtB.eaaz53xwpc
                    section.data(36).logicalSrcIdx = 35;
                    section.data(36).dtTransOffset = 53;

                    ;% rtB.k4rsarzudt
                    section.data(37).logicalSrcIdx = 36;
                    section.data(37).dtTransOffset = 54;

                    ;% rtB.brto0brqox
                    section.data(38).logicalSrcIdx = 37;
                    section.data(38).dtTransOffset = 55;

                    ;% rtB.awrzvcwo5i
                    section.data(39).logicalSrcIdx = 38;
                    section.data(39).dtTransOffset = 56;

                    ;% rtB.pyzaziws5o
                    section.data(40).logicalSrcIdx = 39;
                    section.data(40).dtTransOffset = 57;

                    ;% rtB.kq5jwacnoy
                    section.data(41).logicalSrcIdx = 40;
                    section.data(41).dtTransOffset = 58;

                    ;% rtB.i31yhmvgpf
                    section.data(42).logicalSrcIdx = 41;
                    section.data(42).dtTransOffset = 59;

                    ;% rtB.oh3csxrczc
                    section.data(43).logicalSrcIdx = 42;
                    section.data(43).dtTransOffset = 60;

                    ;% rtB.ncz3ei0xyl
                    section.data(44).logicalSrcIdx = 43;
                    section.data(44).dtTransOffset = 61;

                    ;% rtB.lezl4badfl
                    section.data(45).logicalSrcIdx = 45;
                    section.data(45).dtTransOffset = 62;

                    ;% rtB.mmpoyjb255
                    section.data(46).logicalSrcIdx = 46;
                    section.data(46).dtTransOffset = 63;

                    ;% rtB.et115tvd5c
                    section.data(47).logicalSrcIdx = 47;
                    section.data(47).dtTransOffset = 64;

                    ;% rtB.icsedlrfmo
                    section.data(48).logicalSrcIdx = 49;
                    section.data(48).dtTransOffset = 65;

                    ;% rtB.keu13zucmw
                    section.data(49).logicalSrcIdx = 51;
                    section.data(49).dtTransOffset = 66;

                    ;% rtB.hlen4hvuex
                    section.data(50).logicalSrcIdx = 53;
                    section.data(50).dtTransOffset = 67;

                    ;% rtB.maef41dty2
                    section.data(51).logicalSrcIdx = 54;
                    section.data(51).dtTransOffset = 68;

                    ;% rtB.dvhqwvadlh
                    section.data(52).logicalSrcIdx = 55;
                    section.data(52).dtTransOffset = 69;

                    ;% rtB.fauyn5g1jz
                    section.data(53).logicalSrcIdx = 58;
                    section.data(53).dtTransOffset = 71;

                    ;% rtB.edm5gwau3m
                    section.data(54).logicalSrcIdx = 60;
                    section.data(54).dtTransOffset = 72;

                    ;% rtB.d5igmkwwvg
                    section.data(55).logicalSrcIdx = 61;
                    section.data(55).dtTransOffset = 73;

            nTotData = nTotData + section.nData;
            sigMap.sections(1) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.g4x1kcgl20
                    section.data(1).logicalSrcIdx = 63;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(2) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.kg410grc4m.pveoae0rgk
                    section.data(1).logicalSrcIdx = 64;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(3) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.jty1wsfjlj.pveoae0rgk
                    section.data(1).logicalSrcIdx = 65;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(4) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtB.emmdqoheic.pveoae0rgk
                    section.data(1).logicalSrcIdx = 66;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            sigMap.sections(5) = section;
            clear section


            ;%
            ;% Non-auto Data (signal)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        sigMap.nTotData = nTotData;



    ;%*******************
    ;% Create DWork Map *
    ;%*******************
    
        nTotData      = 0; %add to this count as we go
        nTotSects     = 17;
        sectIdxOffset = 5;

        ;%
        ;% Define dummy sections & preallocate arrays
        ;%
        dumSection.nData = -1;
        dumSection.data  = [];

        dumData.logicalSrcIdx = -1;
        dumData.dtTransOffset = -1;

        ;%
        ;% Init/prealloc dworkMap
        ;%
        dworkMap.nSections           = nTotSects;
        dworkMap.sectIdxOffset       = sectIdxOffset;
            dworkMap.sections(nTotSects) = dumSection; %prealloc
        dworkMap.nTotData            = -1;

        ;%
        ;% Auto data (rtDW)
        ;%
            section.nData     = 18;
            section.data(18)  = dumData; %prealloc

                    ;% rtDW.g2db00oyvj
                    section.data(1).logicalSrcIdx = 0;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.lc2ze5kdtm
                    section.data(2).logicalSrcIdx = 1;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.ki15zaj1gp
                    section.data(3).logicalSrcIdx = 2;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.gymfqxh2cd
                    section.data(4).logicalSrcIdx = 3;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.dt2ijnggmb
                    section.data(5).logicalSrcIdx = 4;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.byvsnyv5zr
                    section.data(6).logicalSrcIdx = 5;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.cz435ihcu3
                    section.data(7).logicalSrcIdx = 6;
                    section.data(7).dtTransOffset = 6;

                    ;% rtDW.ceat33yomo
                    section.data(8).logicalSrcIdx = 7;
                    section.data(8).dtTransOffset = 7;

                    ;% rtDW.np4v4eaezh
                    section.data(9).logicalSrcIdx = 8;
                    section.data(9).dtTransOffset = 8;

                    ;% rtDW.nhi0bwiqwe
                    section.data(10).logicalSrcIdx = 9;
                    section.data(10).dtTransOffset = 9;

                    ;% rtDW.jpmcmrdt3a
                    section.data(11).logicalSrcIdx = 10;
                    section.data(11).dtTransOffset = 10;

                    ;% rtDW.ocgieankjr
                    section.data(12).logicalSrcIdx = 11;
                    section.data(12).dtTransOffset = 11;

                    ;% rtDW.j4bzixxmjs
                    section.data(13).logicalSrcIdx = 12;
                    section.data(13).dtTransOffset = 12;

                    ;% rtDW.ma3yw4utkh
                    section.data(14).logicalSrcIdx = 13;
                    section.data(14).dtTransOffset = 13;

                    ;% rtDW.mfjr5e14xs
                    section.data(15).logicalSrcIdx = 14;
                    section.data(15).dtTransOffset = 14;

                    ;% rtDW.jnortiucxw
                    section.data(16).logicalSrcIdx = 15;
                    section.data(16).dtTransOffset = 15;

                    ;% rtDW.ocj52bygmn
                    section.data(17).logicalSrcIdx = 16;
                    section.data(17).dtTransOffset = 16;

                    ;% rtDW.m4pexi1xka
                    section.data(18).logicalSrcIdx = 17;
                    section.data(18).dtTransOffset = 17;

            nTotData = nTotData + section.nData;
            dworkMap.sections(1) = section;
            clear section

            section.nData     = 39;
            section.data(39)  = dumData; %prealloc

                    ;% rtDW.gbqvg1m3jx.AS
                    section.data(1).logicalSrcIdx = 18;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.dattaamiez.LoggedData
                    section.data(2).logicalSrcIdx = 19;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.e1hczf4cdw.LoggedData
                    section.data(3).logicalSrcIdx = 20;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.kczid045yc.AQHandles
                    section.data(4).logicalSrcIdx = 21;
                    section.data(4).dtTransOffset = 6;

                    ;% rtDW.bud5p4ylzh.AQHandles
                    section.data(5).logicalSrcIdx = 22;
                    section.data(5).dtTransOffset = 9;

                    ;% rtDW.c2q5edz2l4.LoggedData
                    section.data(6).logicalSrcIdx = 23;
                    section.data(6).dtTransOffset = 10;

                    ;% rtDW.kl40m4aiu1.LoggedData
                    section.data(7).logicalSrcIdx = 24;
                    section.data(7).dtTransOffset = 13;

                    ;% rtDW.hbttiet0jp.LoggedData
                    section.data(8).logicalSrcIdx = 25;
                    section.data(8).dtTransOffset = 14;

                    ;% rtDW.dpspcviro2.LoggedData
                    section.data(9).logicalSrcIdx = 26;
                    section.data(9).dtTransOffset = 15;

                    ;% rtDW.cbcqpgn2wv.LoggedData
                    section.data(10).logicalSrcIdx = 27;
                    section.data(10).dtTransOffset = 16;

                    ;% rtDW.mrkhfmmtjl.LoggedData
                    section.data(11).logicalSrcIdx = 28;
                    section.data(11).dtTransOffset = 17;

                    ;% rtDW.o3vmxbgb5q.AQHandles
                    section.data(12).logicalSrcIdx = 29;
                    section.data(12).dtTransOffset = 19;

                    ;% rtDW.iy52gcogzn.AQHandles
                    section.data(13).logicalSrcIdx = 30;
                    section.data(13).dtTransOffset = 20;

                    ;% rtDW.absz4cicrc.LoggedData
                    section.data(14).logicalSrcIdx = 31;
                    section.data(14).dtTransOffset = 21;

                    ;% rtDW.ozhzy31iuu.LoggedData
                    section.data(15).logicalSrcIdx = 32;
                    section.data(15).dtTransOffset = 23;

                    ;% rtDW.kcoagubkix.LoggedData
                    section.data(16).logicalSrcIdx = 33;
                    section.data(16).dtTransOffset = 25;

                    ;% rtDW.meknrp2ozl.LoggedData
                    section.data(17).logicalSrcIdx = 34;
                    section.data(17).dtTransOffset = 26;

                    ;% rtDW.ind2n2fwfq.LoggedData
                    section.data(18).logicalSrcIdx = 35;
                    section.data(18).dtTransOffset = 28;

                    ;% rtDW.aw4hejyc1j.LoggedData
                    section.data(19).logicalSrcIdx = 36;
                    section.data(19).dtTransOffset = 30;

                    ;% rtDW.hg3xctwmjf.LoggedData
                    section.data(20).logicalSrcIdx = 37;
                    section.data(20).dtTransOffset = 32;

                    ;% rtDW.kqu3zaaghu.LoggedData
                    section.data(21).logicalSrcIdx = 38;
                    section.data(21).dtTransOffset = 34;

                    ;% rtDW.dhj4j2gsii.LoggedData
                    section.data(22).logicalSrcIdx = 39;
                    section.data(22).dtTransOffset = 36;

                    ;% rtDW.ef1bsau5gf.LoggedData
                    section.data(23).logicalSrcIdx = 40;
                    section.data(23).dtTransOffset = 38;

                    ;% rtDW.g4pjr2qd2l.LoggedData
                    section.data(24).logicalSrcIdx = 41;
                    section.data(24).dtTransOffset = 40;

                    ;% rtDW.f21icutcu2.AQHandles
                    section.data(25).logicalSrcIdx = 42;
                    section.data(25).dtTransOffset = 43;

                    ;% rtDW.an4rwyup45.AQHandles
                    section.data(26).logicalSrcIdx = 43;
                    section.data(26).dtTransOffset = 44;

                    ;% rtDW.nigjqkrdgh.AQHandles
                    section.data(27).logicalSrcIdx = 44;
                    section.data(27).dtTransOffset = 45;

                    ;% rtDW.pqr5ti5djs.AQHandles
                    section.data(28).logicalSrcIdx = 45;
                    section.data(28).dtTransOffset = 46;

                    ;% rtDW.lrm1xxluc3.LoggedData
                    section.data(29).logicalSrcIdx = 46;
                    section.data(29).dtTransOffset = 47;

                    ;% rtDW.depn2qjdxo.LoggedData
                    section.data(30).logicalSrcIdx = 47;
                    section.data(30).dtTransOffset = 49;

                    ;% rtDW.cgbb10j21u.LoggedData
                    section.data(31).logicalSrcIdx = 48;
                    section.data(31).dtTransOffset = 51;

                    ;% rtDW.ink55qldzx.AQHandles
                    section.data(32).logicalSrcIdx = 49;
                    section.data(32).dtTransOffset = 53;

                    ;% rtDW.bhkkrlprsc.AQHandles
                    section.data(33).logicalSrcIdx = 50;
                    section.data(33).dtTransOffset = 54;

                    ;% rtDW.kxwhg3dymm.AQHandles
                    section.data(34).logicalSrcIdx = 51;
                    section.data(34).dtTransOffset = 55;

                    ;% rtDW.gyf1oq3zs3.AQHandles
                    section.data(35).logicalSrcIdx = 52;
                    section.data(35).dtTransOffset = 56;

                    ;% rtDW.ipoiwfl4sg.AQHandles
                    section.data(36).logicalSrcIdx = 53;
                    section.data(36).dtTransOffset = 57;

                    ;% rtDW.kanxmkuey4.AQHandles
                    section.data(37).logicalSrcIdx = 54;
                    section.data(37).dtTransOffset = 58;

                    ;% rtDW.ezwmkd5spv.LoggedData
                    section.data(38).logicalSrcIdx = 55;
                    section.data(38).dtTransOffset = 59;

                    ;% rtDW.g31trfxw3l.LoggedData
                    section.data(39).logicalSrcIdx = 56;
                    section.data(39).dtTransOffset = 61;

            nTotData = nTotData + section.nData;
            dworkMap.sections(2) = section;
            clear section

            section.nData     = 7;
            section.data(7)  = dumData; %prealloc

                    ;% rtDW.bwi4ak5yob
                    section.data(1).logicalSrcIdx = 57;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.bl3wth4gb4
                    section.data(2).logicalSrcIdx = 58;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.d4deydkd2e
                    section.data(3).logicalSrcIdx = 59;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.dy3zgavjvw
                    section.data(4).logicalSrcIdx = 60;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.hxmang4whi
                    section.data(5).logicalSrcIdx = 61;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.gmsb5tf0og
                    section.data(6).logicalSrcIdx = 62;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.d0lzng0qrp
                    section.data(7).logicalSrcIdx = 63;
                    section.data(7).dtTransOffset = 6;

            nTotData = nTotData + section.nData;
            dworkMap.sections(3) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtDW.cv41it4amb
                    section.data(1).logicalSrcIdx = 64;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.pwmwjft1gn
                    section.data(2).logicalSrcIdx = 65;
                    section.data(2).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            dworkMap.sections(4) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.fy0bl2dcyx
                    section.data(1).logicalSrcIdx = 66;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(5) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtDW.nnw34mmyux
                    section.data(1).logicalSrcIdx = 67;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.fih3gfro2h
                    section.data(2).logicalSrcIdx = 68;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(6) = section;
            clear section

            section.nData     = 8;
            section.data(8)  = dumData; %prealloc

                    ;% rtDW.psfjb0nsls
                    section.data(1).logicalSrcIdx = 69;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.pvevgoy3y3
                    section.data(2).logicalSrcIdx = 70;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.lni3dmfvjj
                    section.data(3).logicalSrcIdx = 71;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.ifed2xuv2w
                    section.data(4).logicalSrcIdx = 72;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.nr4jtirdwo
                    section.data(5).logicalSrcIdx = 73;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.ocwaun5q5s
                    section.data(6).logicalSrcIdx = 74;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.mkoxzdqwi2
                    section.data(7).logicalSrcIdx = 75;
                    section.data(7).dtTransOffset = 6;

                    ;% rtDW.akjewdlwej
                    section.data(8).logicalSrcIdx = 76;
                    section.data(8).dtTransOffset = 7;

            nTotData = nTotData + section.nData;
            dworkMap.sections(7) = section;
            clear section

            section.nData     = 13;
            section.data(13)  = dumData; %prealloc

                    ;% rtDW.cuak05qrvl
                    section.data(1).logicalSrcIdx = 77;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.ocbrfohdqu
                    section.data(2).logicalSrcIdx = 78;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.g5jwl0rrph
                    section.data(3).logicalSrcIdx = 79;
                    section.data(3).dtTransOffset = 2;

                    ;% rtDW.ftys1qypo0
                    section.data(4).logicalSrcIdx = 80;
                    section.data(4).dtTransOffset = 3;

                    ;% rtDW.jl5a3sor32
                    section.data(5).logicalSrcIdx = 81;
                    section.data(5).dtTransOffset = 4;

                    ;% rtDW.k4luewptuo
                    section.data(6).logicalSrcIdx = 82;
                    section.data(6).dtTransOffset = 5;

                    ;% rtDW.obc0rz1ip3
                    section.data(7).logicalSrcIdx = 83;
                    section.data(7).dtTransOffset = 6;

                    ;% rtDW.nghwbebn4m
                    section.data(8).logicalSrcIdx = 84;
                    section.data(8).dtTransOffset = 7;

                    ;% rtDW.cflpbnskfq
                    section.data(9).logicalSrcIdx = 85;
                    section.data(9).dtTransOffset = 8;

                    ;% rtDW.h3rmilnlg1
                    section.data(10).logicalSrcIdx = 86;
                    section.data(10).dtTransOffset = 9;

                    ;% rtDW.dntfct2nvq
                    section.data(11).logicalSrcIdx = 87;
                    section.data(11).dtTransOffset = 10;

                    ;% rtDW.gkeivfk3do
                    section.data(12).logicalSrcIdx = 88;
                    section.data(12).dtTransOffset = 11;

                    ;% rtDW.pqj3y2oaqf
                    section.data(13).logicalSrcIdx = 89;
                    section.data(13).dtTransOffset = 12;

            nTotData = nTotData + section.nData;
            dworkMap.sections(8) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtDW.kg410grc4m.lol2meeg5o
                    section.data(1).logicalSrcIdx = 90;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.kg410grc4m.adakvlvgf4
                    section.data(2).logicalSrcIdx = 91;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(9) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.kg410grc4m.kejdnwv5ef
                    section.data(1).logicalSrcIdx = 92;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(10) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtDW.kg410grc4m.epw5r2ybkp
                    section.data(1).logicalSrcIdx = 93;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.kg410grc4m.gkvboyiwt2
                    section.data(2).logicalSrcIdx = 94;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.kg410grc4m.ogzjxpnwsq
                    section.data(3).logicalSrcIdx = 95;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            dworkMap.sections(11) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtDW.jty1wsfjlj.lol2meeg5o
                    section.data(1).logicalSrcIdx = 96;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.jty1wsfjlj.adakvlvgf4
                    section.data(2).logicalSrcIdx = 97;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(12) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.jty1wsfjlj.kejdnwv5ef
                    section.data(1).logicalSrcIdx = 98;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(13) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtDW.jty1wsfjlj.epw5r2ybkp
                    section.data(1).logicalSrcIdx = 99;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.jty1wsfjlj.gkvboyiwt2
                    section.data(2).logicalSrcIdx = 100;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.jty1wsfjlj.ogzjxpnwsq
                    section.data(3).logicalSrcIdx = 101;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            dworkMap.sections(14) = section;
            clear section

            section.nData     = 2;
            section.data(2)  = dumData; %prealloc

                    ;% rtDW.emmdqoheic.lol2meeg5o
                    section.data(1).logicalSrcIdx = 102;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.emmdqoheic.adakvlvgf4
                    section.data(2).logicalSrcIdx = 103;
                    section.data(2).dtTransOffset = 1;

            nTotData = nTotData + section.nData;
            dworkMap.sections(15) = section;
            clear section

            section.nData     = 1;
            section.data(1)  = dumData; %prealloc

                    ;% rtDW.emmdqoheic.kejdnwv5ef
                    section.data(1).logicalSrcIdx = 104;
                    section.data(1).dtTransOffset = 0;

            nTotData = nTotData + section.nData;
            dworkMap.sections(16) = section;
            clear section

            section.nData     = 3;
            section.data(3)  = dumData; %prealloc

                    ;% rtDW.emmdqoheic.epw5r2ybkp
                    section.data(1).logicalSrcIdx = 105;
                    section.data(1).dtTransOffset = 0;

                    ;% rtDW.emmdqoheic.gkvboyiwt2
                    section.data(2).logicalSrcIdx = 106;
                    section.data(2).dtTransOffset = 1;

                    ;% rtDW.emmdqoheic.ogzjxpnwsq
                    section.data(3).logicalSrcIdx = 107;
                    section.data(3).dtTransOffset = 2;

            nTotData = nTotData + section.nData;
            dworkMap.sections(17) = section;
            clear section


            ;%
            ;% Non-auto Data (dwork)
            ;%


        ;%
        ;% Add final counts to struct.
        ;%
        dworkMap.nTotData = nTotData;



    ;%
    ;% Add individual maps to base struct.
    ;%

    targMap.paramMap  = paramMap;
    targMap.signalMap = sigMap;
    targMap.dworkMap  = dworkMap;

    ;%
    ;% Add checksums to base struct.
    ;%


    targMap.checksum0 = 3882063023;
    targMap.checksum1 = 2812955237;
    targMap.checksum2 = 891024981;
    targMap.checksum3 = 2338554480;


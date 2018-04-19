  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 3;
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
    ;% Auto data (bueufchu5x)
    ;%
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% bueufchu5x.CompareToConstant_const
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% bueufchu5x.AnalogInput3_SampleTime
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% bueufchu5x.AnalogInput2_SampleTime
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% bueufchu5x.AnalogInput1_SampleTime
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% bueufchu5x.Off_Y0
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% bueufchu5x.DigitalInput_SampleTime
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% bueufchu5x.Constant1_Value
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% bueufchu5x.Constant_Value
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% bueufchu5x.Iterations_Y0
	  section.data(1).logicalSrcIdx = 8;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% bueufchu5x.Cpower_Y0
	  section.data(1).logicalSrcIdx = 9;
	  section.data(1).dtTransOffset = 0;
	
	  ;% bueufchu5x.Delay_DelayLength
	  section.data(2).logicalSrcIdx = 10;
	  section.data(2).dtTransOffset = 1;
	
	  ;% bueufchu5x.Delay_InitialCondition
	  section.data(3).logicalSrcIdx = 11;
	  section.data(3).dtTransOffset = 2;
	
	  ;% bueufchu5x.Delay1_DelayLength
	  section.data(4).logicalSrcIdx = 12;
	  section.data(4).dtTransOffset = 3;
	
	  ;% bueufchu5x.Delay1_InitialCondition
	  section.data(5).logicalSrcIdx = 13;
	  section.data(5).dtTransOffset = 4;
	
	  ;% bueufchu5x.Delay2_DelayLength
	  section.data(6).logicalSrcIdx = 14;
	  section.data(6).dtTransOffset = 5;
	
	  ;% bueufchu5x.Delay2_InitialCondition
	  section.data(7).logicalSrcIdx = 15;
	  section.data(7).dtTransOffset = 6;
	
	  ;% bueufchu5x.Delay3_DelayLength
	  section.data(8).logicalSrcIdx = 16;
	  section.data(8).dtTransOffset = 7;
	
	  ;% bueufchu5x.Delay3_InitialCondition
	  section.data(9).logicalSrcIdx = 17;
	  section.data(9).dtTransOffset = 8;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
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
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (octfzwomcvr)
    ;%
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% octfzwomcvr.posoug0pd5
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% octfzwomcvr.jikroj2vsw
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% octfzwomcvr.cjr5kq4qwd
	  section.data(1).logicalSrcIdx = 2;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% octfzwomcvr.agxy4bjxmq
	  section.data(1).logicalSrcIdx = 3;
	  section.data(1).dtTransOffset = 0;
	
	  ;% octfzwomcvr.lfffg1rdih
	  section.data(2).logicalSrcIdx = 4;
	  section.data(2).dtTransOffset = 1;
	
	  ;% octfzwomcvr.hok1rs5ul0
	  section.data(3).logicalSrcIdx = 5;
	  section.data(3).dtTransOffset = 2;
	
	  ;% octfzwomcvr.icfzue1yvr
	  section.data(4).logicalSrcIdx = 6;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% octfzwomcvr.l2vlxihjlw
	  section.data(1).logicalSrcIdx = 7;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
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
    nTotSects     = 6;
    sectIdxOffset = 4;
    
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
    ;% Auto data (dbeoe4zbkeh)
    ;%
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% dbeoe4zbkeh.caansefyhx
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% dbeoe4zbkeh.k4vmarrrpj
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% dbeoe4zbkeh.pk3ygz25dl
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% dbeoe4zbkeh.bue3ua15ub
	  section.data(1).logicalSrcIdx = 3;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% dbeoe4zbkeh.ajil1ufdi5
	  section.data(1).logicalSrcIdx = 4;
	  section.data(1).dtTransOffset = 0;
	
	  ;% dbeoe4zbkeh.hko3uxth2q
	  section.data(2).logicalSrcIdx = 5;
	  section.data(2).dtTransOffset = 1;
	
	  ;% dbeoe4zbkeh.dwffpsko0b
	  section.data(3).logicalSrcIdx = 6;
	  section.data(3).dtTransOffset = 2;
	
	  ;% dbeoe4zbkeh.hxdvn5tda5
	  section.data(4).logicalSrcIdx = 7;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 4;
      section.data(4)  = dumData; %prealloc
      
	  ;% dbeoe4zbkeh.pl4mcyx0ku
	  section.data(1).logicalSrcIdx = 8;
	  section.data(1).dtTransOffset = 0;
	
	  ;% dbeoe4zbkeh.bryk2cngm5
	  section.data(2).logicalSrcIdx = 9;
	  section.data(2).dtTransOffset = 1;
	
	  ;% dbeoe4zbkeh.evrizlb13r
	  section.data(3).logicalSrcIdx = 10;
	  section.data(3).dtTransOffset = 2;
	
	  ;% dbeoe4zbkeh.lzq5v5efr0
	  section.data(4).logicalSrcIdx = 11;
	  section.data(4).dtTransOffset = 3;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% dbeoe4zbkeh.oakue1qmt5
	  section.data(1).logicalSrcIdx = 12;
	  section.data(1).dtTransOffset = 0;
	
	  ;% dbeoe4zbkeh.pr0zefxspj
	  section.data(2).logicalSrcIdx = 13;
	  section.data(2).dtTransOffset = 1;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% dbeoe4zbkeh.ed1wsrwp00
	  section.data(1).logicalSrcIdx = 14;
	  section.data(1).dtTransOffset = 0;
	
	  ;% dbeoe4zbkeh.ezy1l5lmre
	  section.data(2).logicalSrcIdx = 15;
	  section.data(2).dtTransOffset = 1;
	
	  ;% dbeoe4zbkeh.m4ev2uj4yq
	  section.data(3).logicalSrcIdx = 16;
	  section.data(3).dtTransOffset = 2;
	
	  ;% dbeoe4zbkeh.n1e1elpxcd
	  section.data(4).logicalSrcIdx = 17;
	  section.data(4).dtTransOffset = 3;
	
	  ;% dbeoe4zbkeh.awonqgcvrl
	  section.data(5).logicalSrcIdx = 18;
	  section.data(5).dtTransOffset = 4;
	
	  ;% dbeoe4zbkeh.igildgzghv
	  section.data(6).logicalSrcIdx = 19;
	  section.data(6).dtTransOffset = 5;
	
	  ;% dbeoe4zbkeh.oxmqu3lwtu
	  section.data(7).logicalSrcIdx = 20;
	  section.data(7).dtTransOffset = 6;
	
	  ;% dbeoe4zbkeh.pzzqzat2ai
	  section.data(8).logicalSrcIdx = 21;
	  section.data(8).dtTransOffset = 7;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
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


  targMap.checksum0 = 2283371595;
  targMap.checksum1 = 1187396892;
  targMap.checksum2 = 195356857;
  targMap.checksum3 = 3557207949;


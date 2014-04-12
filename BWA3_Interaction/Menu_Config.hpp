
#define HSPACE 0.5-2.0/16/2
#define VSPACE 0.5-0.3/9/2

class BWA3_Interaction_Button_Base {
  tooltip = "";
  action = "";

  idc = -1;
  access = 0;
  style = 0;
  type = 1;
  text = "";
  font = "PuristaMedium";
  sizeEx = "1 / 40 / (getResolution select 5) / (16 / 9) * (getResolution select 4)";
  shadow = 2;

  x = 0;
  y = 0;
  w = 0;
  h = 0;

  offsetX = 0.003;
  offsetY = 0.003;
  offsetPressedX = 0.002;
  offsetPressedY = 0.002;
  borderSize = 0;

  colorText[] = {1,1,1,1};
  colorDisabled[] = {0.5,0.5,0.5,1};
  colorBackground[] = {0,0,0,0.8};
  colorBackgroundDisabled[] = {0,0,0,0.8};
  colorBackgroundActive[] = {1,1,1,0.8};
  colorFocused[] = {0,0,0,0.8};
  colorShadow[] = {0,0,0,0};
  colorBorder[] = {1,1,1,0.8};

  soundEnter[] = {"\A3\ui_f\data\sound\RscButton\soundEnter",0.09,1};
  soundPush[] = {"\A3\ui_f\data\sound\RscButton\soundPush",0.09,1};
  soundClick[] = {"\A3\ui_f\data\sound\RscButton\soundClick",0.09,1};
  soundEscape[] = {"\A3\ui_f\data\sound\RscButton\soundEscape",0.09,1};
};

class BWA3_Interaction_Dialog {
  idd = -1;
  enableSimulation = true;
  movingEnable = false;
  onLoad = "_dlgInteractionDialog = _this select 0; for '_a' from 10 to 19 do {(_dlgInteractionDialog displayCtrl _a) ctrlShow false}; uiNamespace setVariable ['BWA3_Interaction_Dialog', _dlgInteractionDialog];"
  objects[] = {};

  class controls {
    /*
    class Interaction_BWA3_Logo : BWA3_Interaction_Button_Base {
      action = "closeDialog 0;";
      type = 0;
      style = 48;
      //onMouseEnter = "hint ('_' + str(_this))";
      tooltip = "";
      text = "\bwa3_common\rsc\bwlogo.paa";
      idc = 2;
      x = (0.5-1.0/16/2 + 0 * 0.1) * safezoneW + safezoneX;
      y = (0.5-1.0/9/2 + 0 * 0.04) * safezoneH + safezoneY;
      w = 1.0 / 16 * safezoneW;
      h = 1.0 / 9 * safezoneH;
    };
    */
    class Interaction_ButtonMain : BWA3_Interaction_Button_Base {
      action = "call compile BWA3_Interaction_MainButton";
      style = 2;
      tooltip = "";
      text = "Interaction Menu";
      idc = 2;
      sizeEx = "0.8 / 40 / (getResolution select 5) / (16 / 9) * (getResolution select 4)";
      x = (0.5-1.8/16/2 + 0 * 0.1) * safezoneW + safezoneX;
      y = (0.5-0.55/9/2 + 0 * 0.04) * safezoneH + safezoneY;
      w = 1.8 / 16 * safezoneW;
      h = 0.55 / 9 * safezoneH;
    };    

    class Interaction_Button0 : BWA3_Interaction_Button_Base {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 0; if (call (_action select 2)) then {call (_action select 1)};";
      style = 2;
      tooltip = "";
      text = "";
      idc = 10;
      x = (HSPACE + 0 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE - 2.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };

    class Interaction_Button1 : Interaction_Button0 {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 1; if (call (_action select 2)) then {call (_action select 1)};";
      tooltip = "";
      text = "";
      idc = 11;
      x = (HSPACE + 1.0 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE - 1.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };

    class Interaction_Button2 : Interaction_Button0 {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 2; if (call (_action select 2)) then {call (_action select 1)};";
      tooltip = "";
      text = "";
      idc = 12;
      x = (HSPACE + 1.25 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE - 0.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };

    class Interaction_Button3 : Interaction_Button0 {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 3; if (call (_action select 2)) then {call (_action select 1)};";
      tooltip = "";
      text = "";
      idc = 13;
      x = (HSPACE + 1.25 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE + 0.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };

    class Interaction_Button4 : Interaction_Button0 {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 4; if (call (_action select 2)) then {call (_action select 1)};";
      tooltip = "";
      text = "";
      idc = 14;
      x = (HSPACE + 1.0 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE + 1.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };

    class Interaction_Button5 : Interaction_Button0 {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 5; if (call (_action select 2)) then {call (_action select 1)};";
      tooltip = "";
      text = "";
      idc = 15;
      x = (HSPACE + 0 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE + 2.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };

    class Interaction_Button6 : Interaction_Button0 {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 6; if (call (_action select 2)) then {call (_action select 1)};";
      tooltip = "";
      text = "";
      idc = 16;
      x = (HSPACE - 1.0 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE + 1.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };

    class Interaction_Button7 : Interaction_Button0 {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 7; if (call (_action select 2)) then {call (_action select 1)};";
      tooltip = "";
      text = "";
      idc = 17;
      x = (HSPACE - 1.25 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE + 0.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };

    class Interaction_Button8 : Interaction_Button0 {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 8; if (call (_action select 2)) then {call (_action select 1)};";
      tooltip = "";
      text = "";
      idc = 18;
      x = (HSPACE - 1.25 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE - 0.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };

    class Interaction_Button9 : Interaction_Button0 {
      action = "closeDialog 0; _action = BWA3_Interaction_Buttons select 9; if (call (_action select 2)) then {call (_action select 1)};";
      tooltip = "";
      text = "";
      idc = 19;
      x = (HSPACE - 1.0 * 0.1) * safezoneW + safezoneX;
      y = (VSPACE - 1.5 * 0.04) * safezoneH + safezoneY;
      w = 2.0 / 16 * safezoneW;
      h = 0.3 / 9 * safezoneH;
    };
  };
};

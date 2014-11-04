/*
 * Author: KoffeinFlummi
 *
 * Called when some dude gets shot. Or stabbed. Or blown up. Or pushed off a cliff. Or hit by a car. Or burnt. Or poisoned. Or gassed. Or cut. You get the idea.
 *
 * Arguments:
 * 0: Unit that got hit (Object)
 * 1: Name of the selection that was hit (String); "" for structural damage
 * 2: Amount of damage inflicted (Number)
 * 3: Shooter (Object); Null for explosion damage, falling, fire etc.
 * 4: Projectile (Object)
 *
 * Return value:
 * Damage value to be inflicted (optional)
 */

#define UNCONSCIOUSNESSTHRESHOLD 0.5

#define LEGDAMAGETHRESHOLD1 1
#define LEGDAMAGETHRESHOLD2 1.7
#define ARMDAMAGETHRESHOLD 1.7

#define PAINKILLERTHRESHOLD 0.1
#define PAINLOSS 0.0001

#define BLOODTHRESHOLD1 0.35
#define BLOODTHRESHOLD2 0
#define BLOODLOSSRATE 0.02

private ["_unit", "_selectionName", "_damage", "_source", "_source", "_projectile", "_hitSelections", "_hitPoints", "_newDamage", "_found", "_preventDeath"];

_unit          = _this select 0;
_selectionName = _this select 1;
_damage        = _this select 2;
_source        = _this select 3;
_projectile    = _this select 4;

// Prevent unnecessary processing
if (damage _unit == 1) exitWith {};

_unit setVariable ["AGM_Diagnosed", False, True];

// @todo custom eventhandlers
// @todo: figure out if this still applies.

// For some reason, everything is backwards in MP,
// so we need to untangle some things.
if (isMultiplayer) then {
  // If you add something to this, remember not to replace something twice.
  if (_selectionName == "hand_r") then {
    _selectionName = "leg_l";
  };
  if (_selectionName == "leg_r") then {
    _selectionName = "hand_l";
  };
  if (_selectionName == "legs") then {
    _selectionName = "hand_r";
  };
};

// This seems to only show up in MP too, but since it doesn't
// collide with anything, I'll check it in SP as well.
if (_selectionName == "r_femur_hit") then {
  _selectionName = "leg_r";
};

_hitSelections = ["head", "body", "hand_l", "hand_r", "leg_l", "leg_r"];
_hitPoints = ["HitHead", "HitBody", "HitLeftArm", "HitRightArm", "HitLeftLeg", "HitRightLeg"];

// If the damage is being weird, we just tell it to fuck off.
if !(_selectionName in (_hitSelections + [""])) exitWith {0};

// Calculate change in damage.
_newDamage = _damage - (damage _unit);
if (_selectionName in _hitSelections) then {
  _newDamage = _damage - (_unit getHitPointDamage (_hitPoints select (_hitSelections find _selectionName)));
};

// Finished with the current frame, reset variables
if (isNil "AGM_Medical_FrameNo" or {diag_framno > AGM_Medical_FrameNo}) then {
  AGM_Medical_FrameNo = diag_frameno;
  AGM_Medical_isFalling = False;
  AGM_Medical_Projectiles = [];
  AGM_Medical_HitPoints = [];
  AGM_Medical_Damages = [];
};

_damage = _damage - _newDamage;

_newDamage = _newDamage * AGM_Medical_CoefDamage;

// Exclude falling damage to everything other than legs, halve the structural damage.
// @todo Figure out why this still doesn't work
if (((velocity _unit) select 2 < -5) and (vehicle _unit == _unit)) then {
  AGM_Medical_isFalling = True;
};
if (AGM_Medical_isFalling and !(_selectionName in ["", "leg_l", "leg_r"])) exitWith {
  _unit getHitPointDamage (_hitPoints select (_hitSelections find _selectionName));
};
if (AGM_Medical_isFalling) {
  _newDamage = _newDamage / 2;
};

// Make sure there's only one damage per selection.
if (_selectionName != "") then {
  if (_projectile in AGM_Medical_Projectiles) then {
    _index = AGM_Medical_Projectiles find _projectile;
    _otherDamage = (AGM_Medical_Damages select _index);
    if (_otherDamage > _newDamage) then {
      _newDamage = 0;
    } else {
      _hitPoint = AGM_Medical_HitPoints select _index;
      _restore = ((_unit getHitPointDamage _hitPoint) - _otherDamage) max 0;
      _unit setHitPointDamage [_hitPoint, _restore];
      // Make entry unfindable
      AGM_Medical_Projectiles set [_index, objNull];
      AGM_Medical_Projectiles pushBack _projectile;
      AGM_Medical_HitPoints pushBack (_hitPoints select (_hitSelections find _selectionName));
      AGM_Medical_Damages pushBack _newDamage;
    };
  } else {
    AGM_Medical_Projectiles pushBack _projectile;
    AGM_Medical_HitPoints pushBack (_hitPoints select (_hitSelections find _selectionName));
    AGM_Medical_Damages pushBack _newDamage;
  };
};

_damage = _damage + _newDamage;

// @todo: assign orphan structural damage to torso (preferably without spawn)

// Leg Damage
_legDamage = (_unit getHitPointDamage "HitLeftLeg") + (_unit getHitPointDamage "HitRightLeg");
if (_selectionName == "leg_l") then {
  _legDamage = _damage + (_unit getHitPointDamage "HitRightLeg");
};
if (_selectionName == "leg_r") then {
  _legDamage = (_unit getHitPointDamage "HitLeftLeg") + _damage;
};
// lightly wounded, only limit walking speed (forceWalk is for suckers)
if (_legDamage >= LEGDAMAGETRESHOLD1) {
  _unit setHitPointDamage ["HitLegs", 1];
else {
  _unit setHitPointDamage ["HitLegs", 0];
};
// @ŧodo: force prone for completely fucked up legs.

// Arm Damage
_armdamage = "haha just kidding there's no arm damage.";
_unit setHitPointDamage ["HitHands", 0];

// Unconsciousness
if (_selectionName == "" and _damage >= UNCONSCIOUSNESSTRESHOLD and _damage < 1 and !(_unit getVariable ["AGM_Unconscious", False])) then {
  // random chance to kill AI instead of knocking them out, otherwise
  // there'd be shittons of unconscious people after every firefight, causing
  // executions. And nobody likes executions.
  if (!(isPlayer _unit) and {random 1 > 0.5}) then { // @todo: zeus compatibility
    _damage = 1;
  } else {
    [_unit] call AGM_Medical_fnc_knockOut;
  };
};

// Set Pain
// @todo: reimplement pain effect in clientinit
_potentialPain = _damage * (_unit getVariable "AGM_Painkiller");
if ((_selectionName == "") and (_potentialPain > _unit getVariable "AGM_Pain")) then {
  _unit setVariable ["AGM_Pain", _damage * (_unit getVariable "AGM_Painkiller"), true];
};

// @todo: handle bleeding in clientinit

// ================= EVERYTHING BELOW STILL NEEDS TO BE CHECKED ====================

_preventDeath = false;
// Only prevent death if we are going to handle unconciousness
if (isPlayer _unit or _unit getVariable ["AGM_AllowUnconscious", false]) then {
  if (!(_unit getVariable "AGM_Unconscious") and {AGM_Medical_PreventInstaDeath > 0}) then {
    _preventDeath = true;
  };
  if ((_unit getVariable "AGM_Unconscious") and {AGM_Medical_PreventDeathWhileUnconscious > 0}) then {
    _preventDeath = true;
  };
};

if (_preventDeath and vehicle _unit != _unit and damage (vehicle _unit) >= 1) exitWith {
  _unit setPosATL [(getPos _unit select 0) + (random 3) - 1.5, (getPos _unit select 1) + (random 3) - 1.5, 0];
  [_unit, "HitBody", 0.89, true] call AGM_Medical_fnc_setHitPointDamage;
  [_unit] call AGM_Medical_fnc_knockOut;
  _unit allowDamage false;
  _unit spawn {
    sleep 1;
    _this allowDamage true;
  };
};

if (_preventDeath) then {
  _damage = _damage min 0.89;
};


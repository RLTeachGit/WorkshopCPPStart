// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class My3rdPersonDestTarget : TargetRules
{
	public My3rdPersonDestTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "My3rdPersonDest" } );
	}
}

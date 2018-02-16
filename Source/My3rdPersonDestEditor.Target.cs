// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class My3rdPersonDestEditorTarget : TargetRules
{
	public My3rdPersonDestEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "My3rdPersonDest" } );
	}
}

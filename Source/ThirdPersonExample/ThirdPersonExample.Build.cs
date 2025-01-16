// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class ThirdPersonExample : ModuleRules
{
	public ThirdPersonExample(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "AIModule"
        });

		PublicIncludePaths.AddRange(new string[]
		{
			"ThirdPersonExample/Public/Player",
			"ThirdPersonExample/Public/Player/Animations",
			"ThirdPersonExample/Public/Components",
			"ThirdPersonExample/Public/AI",
			"ThirdPersonExample/Public/AI/Components",
			"ThirdPersonExample/Public/Weapons",
            "ThirdPersonExample/Public/UI",
            "ThirdPersonExample/Public/Menu",
            "ThirdPersonExample/Public/Menu/UI",
			"ThirdPersonExample/Public/Interfaces/CombatSystem",
			"ThirdPersonExample/Public/AbilitySystem",
			"ThirdPersonExample/Public/Dev/DamageTypes",
		});
	}
}

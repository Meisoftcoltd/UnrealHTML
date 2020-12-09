namespace UnrealBuildTool.Rules
{
	public class UnrealHTML : ModuleRules
	{
		public UnrealHTML(ReadOnlyTargetRules Target) : base(Target)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
                    "InputCore",
                    "RenderCore",
                    "RHI",
                    "Slate",
					"SlateCore",
					"UMG"
				}
			);

			// PrivateDependencyModuleNames.AddRange(
			// 	new string[]
			// 	{
			// 		""
			// 	}
			// );

			// if (Target.Type != TargetType.Server)
			// {
			// 	PublicDependencyModuleNames.AddRange(
			// 		new string[]
			// 		{
			// 			"WebBrowser"
			// 		}
			// 	);

			// 	if (Target.bBuildEditor || Target.Platform == UnrealTargetPlatform.Android)
			// 	{
			// 		PrivateIncludePathModuleNames.AddRange(
			// 			new string[]
			// 			{
			// 				"WebBrowserTexture"
			// 			}
			// 		);

			// 		PrivateDependencyModuleNames.AddRange(
			// 			new string[]
			// 			{
			// 				"WebBrowserTexture"
			// 			}
			// 		);
			// 	}
			// }
		}
	}
}

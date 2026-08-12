#include "TestPlugin.h"

#define LOCTEXT_NAMESPACE "FTestPluginModule"

void FTestPluginModule::StartupModule()
{
	// This code executes after your module is loaded into memory.
}

void FTestPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTestPluginModule, TestPlugin)
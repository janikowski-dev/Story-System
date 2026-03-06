#pragma once

class FCinematicTimelineEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void AddMenus() const;
};

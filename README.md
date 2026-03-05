<p align="center">
  <img src="Assets/Logo.png" />
</p>

**Chronicle** is an Unreal Engine plugin for building narrative-driven games. It gives developers a visual way to create branching dialogues, hook up game logic through a rule system, and eventually manage characters, quests, and cinematic timelines - all from within the editor.

## Modules

Chronicle is divided into separate modules for clarity and easier maintenance. Each module has its own detailed README in the `Docs/` folder.

### Dialogue System

![Dialogue System Overview](Assets/Dialogue_System_Overview.png)

[See full Dialogue System documentation →](Docs/DialogueSystem.md)

### Rule System

![Rule System Overview](Assets/Rule_System_Overview.png)

[See full Rule System documentation →](Docs/RuleSystem.md)

### Character System

![Character System Overview](Assets/Character_System_Overview.png)

[See full Character System documentation →](Docs/CharacterSystem.md)

## Roadmap

Future planned modules and features for Chronicle:

1. **Dialogue System Extension:**
- Add full JSON export/import support (to make localization easier)
- Add parametrized rules (to make stat checks easier)

2. **Cinematic Timeline** – in-editor cutscenes and timeline management
3. **Quest Editor** – asset-based quests and branching objectives

## Installation

1.  Clone or download this repository
2.  Place the plugin in: `(Project)/Plugins/Chronicle`
3.  Open the project in Unreal Engine
4.  Enable  **Chronicle**  in: `Edit → Plugins → Tools`
5.  Restart the editor

## Requirements

-   Unreal Engine 5.x
-   Editor build

## How To Use

Usage and integration instructions are included in each module’s README:

- [Dialogue System](Docs/DialogueSystem.md) – Create and manage branching conversations with visual nodes
- [Rule System](Docs/RuleSystem.md) – Define game logic and conditions
- [Character System](Docs/CharacterSystem.md) – Manage characters

## Contributing

Chronicle is open for contributions! If you'd like to help expand features, improve documentation, or provide bug fixes, please fork the repository and submit a pull request.

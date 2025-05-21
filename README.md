# InteractionSystem
 A simple interaction system plugin for Unreal Engine. Part of the Midnight Engine Toolkit used by Moonlit Night Studios.
 This plugin is easy to setup and is extensively used in prototypes in internal projects.

## How To Use

### Setting up the plugin in your project

 1) Add an Interaction Component to your pawn class. Set the radius of the collision sphere as per project requirements.

 2) To every interactable actor class, add the Interactable interface. Override the BeginInteraction and EndInteraction function to implement corrsponding behaviours. You can also override the GetDisplayText to provide the text any UI elements.

### Using the system

  In your game, add a input action for interaction. When the input is triggered and completed, call BeginInteraction and EndInteraction on the Interaction component.
  
  The interaction component manages all interactables in range. The first interactable in the list of known interactables is the "Focussed interactable". This is the one that will be interacted with when calling BeginInteraction and EndInteraction. To set the focussed interactable, call SetFocussedInteractable on the Inetraction component.

  You can get a list of all interactables using GetInteractables.

  Listen to OnInteractablesListChanged to know when the list of interactables changes. This can be used to update the UI.

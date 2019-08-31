# AstroCorps
An hopefully awesome space game in it's first stages of development. 

As of now the core gameplay is going to be based around building and upgrading your space ship to increase its abilites. There will be planets, creatures, and traders. All of which are completely unimplemented as of now :). I have High hopes for it.

Again very early in development but here are the systems that are currently being implmented:
* SFML for window management. Possibly thinking about networking, but definitely using SFML for window management, events, and audio
* TinyXML2, for parsing XML files. The XML files are used to serialize any data that would be needed to accurately save the game state when the application is closed
* Sol3, for parsing and interpreting Lua scripts. My scripting engine is in a very early beta, the game play mechanics have recently been ported to Lua, mostly. The plan is to have most, if not all, game play mechanics expressed in Lua. 

As a side note I have recently moved back into my college dorm, so progress might be a little slower now. Mainly my design process while I'm at school will be to very slowly add features and refactor as much as possible as opposed to pushing new features constantly and then taking a week off to refactor those features.

# LightRSS TODO List

## Core Framework

[x] Add CI/CD
[ ] Use standard format for datetime
[ ] Serialization:
    [x] Subscribed channels (list of URLS)
    [x] Channel Table + Serialization
    [ ] Article Table + Serializeion + Foreign Key (also mark read/unread)
    [ ] Index via GUID so that we can quickly update

## UI

Consider also SDL2 & DearImGui perhaps? Worked well for [LightEngine3's Editor](https://github.com/Mickelbil84/LightEngine3)

[ ] Add WxWidgets as a dependency
[ ] Left panel is a list of all subscribed channels (+ ALL), and you can add/remove
[ ] Right panel is list of all articles, with bottom panel is article content
[ ] Allow ordering the subscribed channels

Overall the layout is:
=======================
 S  |                 |
 U  |  Articles List  |
 B  |-----------------|
 S  |                 |
--- | Article Content |
Add |                 |
=======================
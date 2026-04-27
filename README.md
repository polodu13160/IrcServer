# IrcServer

## Architecture


```mermaid 

graph TD
    %% 1. Compilation
    subgraph Compilation ["1. Compilation (Makefile)"]
        M[Makefile]
        HOST[define.cpp <br/><i>Defines the HOST</i>]
        PORT[define.cpp <br/><i>Defines the default Server Port</i>]
        
        M --->|make| S_BIN["Executable: IrcServer"]
        M --->|make bots| B_BIN["Executable: IrcBot"]
        
        HOST -.->|Configured in| S_BIN
        PORT -.->|Configured in| B_BIN
    end

    %% 2. Execution
    subgraph Execution ["2. Execution Commands"]
        S_RUN["./IrcServer [PORT] [PASSWORD]"]
        B_RUN["./IrcBot"]
    end

    S_BIN --> S_RUN
    B_BIN --> B_RUN

    %% 3. Server Commands
    subgraph Server ["3. IRC Server (src/Commands)"]
        CMDS["PASS, NICK, USER, JOIN, PART,<br>PRIVMSG, NOTICE, MODE,<br>TOPIC, INVITE, KICK, LIST, WHO,<br>QUIT, PONG"]
    end

    S_RUN --- CMDS

    %% 4. Bot Logic
    subgraph Bot ["4. Bot Logic (Automod)"]
        LISTEN["Monitors PRIVMSG"]
        FILE["bot/insult file"]
        CHECK{"Forbidden word?"}
        KICK_CMD["Action: KICK user"]

        B_RUN --> LISTEN
        LISTEN --> CHECK
        FILE -.-> CHECK
        CHECK -- YES --> KICK_CMD
        CHECK -- NO --> LISTEN
    end

    %% Style
    style Compilation fill:#f9f,stroke:#333,stroke-width:2px
    style Execution fill:#bbf,stroke:#333,stroke-width:2px
    style Server fill:#dfd,stroke:#333,stroke-width:2px
    style Bot fill:#ffd,stroke:#333,stroke-width:2px

```

## Makefile

- `make` : compile `IrcServer`.
  - Le host est défini dans `inc/Define.hpp` (macro `HOST`).
- `make bots` : compile `IrcBot` (alias de `make bot`).

## Exécution

- Serveur : `./IrcServer [PORT] [PASSWORD]`
- Bot : `./IrcBot [PORT]`

## IRC Server — commandes implémentées (`src/Commands`)

- `PASS`
- `NICK`
- `USER`
- `JOIN`
- `PART`
- `PRIVMSG`
- `NOTICE`
- `MODE`
- `MODE_utils`
- `TOPIC`
- `INVITE`
- `KICK`
- `LIST`
- `WHO`
- `QUIT`
- `PINGPONG`

## Bot

- Le bot surveille les messages `PRIVMSG`.
- Si un utilisateur envoie un mot interdit (liste dans `bot/insult`) :
  - le bot envoie un `KICK` sur le channel,
  - puis envoie un `PRIVMSG` à l'utilisateur expulsé.

## Sources

https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/

https://www.undernet.org/docs/irc-quit-message-faq

https://modern.ircdocs.horse/#rpltopicwhotime-333

https://mathieu-lemoine.developpez.com/tutoriels/irc/protocole/?page=generalites




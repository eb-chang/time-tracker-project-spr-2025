# Program Order of Operations
## Welcome
* Prompt user with welcome message
    * `Welcome!`

## Login/Sign-up  
```
Please select an option:
1. Log-in
2. Sign-up
```
### Log-in
`Please enter your username: [user input]`  
* If user does not enter char `1` or `2`, reprompt until user enters an appropriate char
* If username is not found in database, prompt user: `Username not found.`, then reprompt with option select

### Sign-up  
`Please enter your password: [user input]`
* If password does not match, prompt user to try again, go back to menu, or quit.

## Successful Login & Timer select
```
Welcome [username]! Please select an option
1. Start a timer
2. Check stats
```

### Start a timer
```
Please select a timer:
1. Classic timer
2. Pomodoro timer
3. Chess timer
```

### Check stats
```
1. Check past 10 timers
2. Check total focus time (chess timer not incl.)
```

> **NOTE:** enough menus to make a <span style=color:yellow>Menu object</span>.

| Menu                           |
|--------------------------------|
|- **int** nOptions              |
|- vector<**string**> optionList |
| + getOptionList                |
| + setOptionList                |
| + addOption                    |
| + validate()                   |

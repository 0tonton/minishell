# minishell
'minishell' team-project from 42 whose goal was to create a basic shell program, following bash as a reference.

## Install
To compile, run the command in the minishell folder : 
```
make
```

To run it:
```
./minishell
```

## Mandatory part
This shell handles:
  - single quote, double quote
  - all redirections (<, >, <<, >>) including HEREDOC
  - simple pipes ('|')
  - environment variables and exit status '$?'
  - signals: CTRL-C (display a new prompt on a new line), CTRL-D (exits the shell on an empty line), CTRL-\ (does nothing)
  - every commands according to the PATH variable apart from those, which are built-ins:

			* cd (with a relative path)
			* pwd (no opt)
			* export (no opt)
			* unset (no opt)
			* env (no opt/args)
			* exit (no opt)


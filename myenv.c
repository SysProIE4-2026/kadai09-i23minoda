/*
 *  myenv.c : env コマンドのクローン
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifdef __linux__
#include "myputenv.h"
#define PUTENV myputenv
#else
#define PUTENV putenv
#endif
extern char **environ; 
int main(int argc, char *argv[]) {
    int i = 1;
    while (i < argc && strchr(argv[i], '=') != NULL) {
        if (PUTENV(argv[i]) != 0) {
            perror("myputenv");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    if (i == argc) {
        for (char **env = environ; *env != NULL; env++) {
            printf("%s\n", *env);
        }
        return 0;
    }
    char *path = argv[i];
    execve(path, &argv[i], environ);
    perror(path);
    return 1;
}
/* 実行例

minodayuu@minodayuunoMacBook-Air kadai09-i23minoda % ./myenv MY_VAR=hello /usr/bin/printenv MY_VAR <-環境変数を変更してコマンドを実行
hello
minodayuu@minodayuunoMacBook-Air kadai09-i23minoda % ./myenv A=1 B=2 C=3 /usr/bin/printenv A B C <-複数の環境変数を同時に変更
1
minodayuu@minodayuunoMacBook-Air kadai09-i23minoda % ./myenv /bin/noexist <-エラー発生時
/bin/noexist: No such file or directory
minodayuu@minodayuunoMacBook-Air kadai09-i23minoda % ./myenv <-一覧表示
TMPDIR=/var/folders/0l/hvt47hk93p9gdfh75f6jr3xr0000gn/T/
__CFBundleIdentifier=com.apple.Terminal
XPC_FLAGS=0x0
LaunchInstanceID=56FCBE51-23B9-4B89-A7E3-0DEDFEEA54F3
TERM=xterm-256color
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.sujgSqk3pY/Listeners
SECURITYSESSIONID=186a2
XPC_SERVICE_NAME=0
TERM_PROGRAM=Apple_Terminal
TERM_PROGRAM_VERSION=455.1
TERM_SESSION_ID=038D73C3-2DCD-4041-8239-12F76F91378F
SHELL=/bin/zsh
HOME=/Users/minodayuu
LOGNAME=minodayuu
USER=minodayuu
PATH=/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/opt/homebrew/bin
SHLVL=1
PWD=/Users/minodayuu/Library/CloudStorage/OneDrive-独立行政法人国立高等専門学校機構/sysproDai2/kadai09-i23minoda
OLDPWD=/Users/minodayuu/Library/CloudStorage/OneDrive-独立行政法人国立高等専門学校機構/sysproDai2
LANG=ja_JP.UTF-8
_=/Users/minodayuu/Library/CloudStorage/OneDrive-烫?竃?胁??惴?泃?人僻?竃?髃?筃?専郶?学惀??橃?槃?/sysproDai2/kadai09-i23minoda/./myenv
minodayuu@minodayuunoMacBook-Air kadai09-i23minoda % ./myenv /bin/ls -l /　<-引数付きコマンドの実行
total 10
drwxrwxr-x  43 root  admin  1376  6 17 14:16 Applications
drwxr-xr-x@ 39 root  wheel  1248  8 17  2025 bin
drwxr-xr-x   2 root  wheel    64 10 18  2022 cores
dr-xr-xr-x   4 root  wheel  4738  6 27 01:31 dev
lrwxr-xr-x@  1 root  wheel    11  8 17  2025 etc -> private/etc
lrwxr-xr-x   1 root  wheel    25  6 27 01:31 home -> /System/Volumes/Data/home
drwxr-xr-x  68 root  wheel  2176  4  8 14:33 Library
drwxr-xr-x   3 root  wheel    96  4 21 09:51 opt
drwxr-xr-x   6 root  wheel   192  6 27 01:31 private
drwxr-xr-x@ 76 root  wheel  2432  8 17  2025 sbin
drwxr-xr-x@ 10 root  wheel   320  8 17  2025 System
lrwxr-xr-x@  1 root  wheel    11  8 17  2025 tmp -> private/tmp
drwxr-xr-x   5 root  admin   160  9  7  2025 Users
drwxr-xr-x@ 11 root  wheel   352  8 17  2025 usr
lrwxr-xr-x@  1 root  wheel    11  8 17  2025 var -> private/var
drwxr-xr-x   3 root  wheel    96  6 29 15:57 Volumes

*/

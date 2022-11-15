# WateringSystem BackEnd - Node.js

## BackEnd Libraries Used
```
"express": "^4.17.1",
"morgan": "^1.10.0",
"mysql2": "^2.1.0",
"sequelize": "^6.3.4",
"sequelize-cli": "^6.2.0"
```

## 개발환경
개발용 PC의 OS는 `windows 10`을 사용 한다.
개발용 디렉토리는 다음과 같다.
`c:\Workspace`
```console
> cd C:\Workspace
```
위 디렉토리로 이동 한다.


## node.js 설치
version: v14.15.4
(nvm을 이용하여 버전관리 할 것. (윈도우용 nvm: [https://github.com/coreybutler/nvm-windows/releases](https://github.com/coreybutler/nvm-windows/releases) ))

```console
> nvm install 14.15.4 64
> nvm use 14.15.4 64
> nvm list
  * 14.15.4 (Currently using 64-bit executable)
    12.20.0
```

## express 설치
`express-generator`를 이용하여 기본 구조를 생성 한다.
https://expressjs.com/ko/starter/generator.html

(참고로 현재 디렉토리는 `C:\Workspace` 이다)

```console
> npm install express-generator -g
> express --ejs nodeproj
```
(프로젝트 이름을 `nodeproj`로 설정 하였다.)

## npm 패키지 설치
위에 생성된 프로젝트 폴더로 이동 한 후 npm을 이용해서 nodejs패키지들을 설치 한다.

```console
> cd nodeproj
> npm install
```



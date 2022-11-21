# WateringSystem BackEnd - Node.js

## BackEnd 개발 환경 설정
```
node.js : v14.16.1
npm : 6.14.12
mysql : 8.0.30
```

## 라이브러리 버전
```
"express": "^4.17.1",
"morgan": "^1.10.0",
"mysql2": "^2.1.0",
"sequelize": "^6.3.4",
"sequelize-cli": "^6.2.0",
"cors": "^2.8.5",
"nodemon": "^2.0.4"
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
version: v14.16.1
(nvm을 이용하여 버전관리 할 것. (윈도우용 nvm: [https://github.com/coreybutler/nvm-windows/releases](https://github.com/coreybutler/nvm-windows/releases) ))


```console
> nvm install 14.16.1 64
> nvm use 14.16.1 64
> nvm list
  * 14.16.1 (Currently using 64-bit executable)
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

## Database 연결
config 폴더에 config.json 파일 설정한다.
development, test, production 에 있는 설정을 자신의 Database설정과 맞춘다.
ex) development
```
"development": {
    "username": "database_name",
    "password": "database_password",
    "database": "nodejs",
    "host": "127.0.0.1",
    "dialect": "mysql"
  }
// 필요한 경우 port를 추가한다.
```

## CORS 설정
config 폴더에 whiteList.json 파일를 설정한다. </br>
cors를 허락 해주는 링크를 설정한다.
```
[
  "http://localhost:8080",
  "http://localhost:8081",
  "http://192.168.0.70:8080",
  "https://nid.naver.com/oauth2.0"
]
```



# CheckService

## 対応仕様

- HTTP : 1.0
- TLS : 1.2

## コマンド

```
// ビルド
make build

// 実行
./check_server <urllist>
```

## urllistの形式

- テキストファイル(.txt)
- URLを改行区切りで書き込む

```
// url_list.txt
https://example.com
https://example.com/path/to/service
```

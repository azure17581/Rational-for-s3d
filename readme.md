# Rational for s3d
OpenSiv3D で有理数を扱う  
v0.6.3 で動作確認

## 導入
`rational.h` をプロジェクトファイルに追加し，これを使いたいファイルに
```c++
#include "rational.h"
```
を追記。

## メソッド
### コンストラクタ
|引数|説明|
|-|-|
|`Rational()`|0 / 1 で初期化|
|`Rational(int32 n, int32 d)`| `n` / `d` の値で初期化 <br> `d` = 0 の時に例外 <br> `std::runtime_error{ "denominator is Zero" }` を投げる|
|`Rational(T val)`| `val` / 1 の値で初期化（`T` は任意の整数型）<br> ただし 32bit 整数を超えた入力をするとオーバーフローする|

### getter / setter
|メソッド名|戻り値型|説明|
|-|-|-|
|`gnum()`|`int32`|分子の値を返す|
|`gden()`|`int32`|分母の値を返す|
|`snum(int32 n)`|`void`|分子の値を `n` にする|
|`sden(int32 n)`|`void`|分母の値を `n` にする <br> `n` = 0 の時に例外 <br> `std::runtime_error{ "denominator is Zero" }` を投げる|
|`setVal(int32 n, int32 d)`|`void`|`n` / `d` の値に設定 <br> `d` = 0 の時に例外 <br> `std::runtime_error{ "denominator is Zero" }` を投げる|

## 演算子
`I` は任意の整数型，`F` は任意の浮動小数型を表す。正確には `I`，`F` はそれぞれ `concept` の `std::integral`， `std::floating_point` に含まれる型をとる。ただし，`Rational` は現在内部的に値を 32bit 整数型で管理している。  
`I`，`Rational` は誤差を含まないが `F` は誤差を含んでいるため，`F` との演算では戻り値を `F` とした。
|引数の型|戻り値型|定義された演算子|
|-|-|-|
|左辺，右辺の一方が `Rational`，<br>他方が `Rational` もしくは `I`|`Rational`|`+`, `-`, `*`, `/`|
|左辺，右辺の一方が `Rational`，<br>他方が `Rational` もしくは `I`|`bool`|`<`, `>`, `<=`, `>=`, `==`, `!=`
|左辺が `Rational`，<br>右辺が `Rational` もしくは `I`|`Rational`|`+=`, `-=`, `*=`, `/=`|
|左辺，右辺の一方が `Rational`，<br>他方が `F`|`F`|`+`, `-`, `*`, `/`|

## その他
`void s3d::Formatter(FormatData& formatData, const Rational& r)` をオーバーロードしているため，`Rational` は `concept s3d::Formattable` を満たす。これによって Siv3d に用意された文字列化 (`Format()`，`Print` など) が利用できる。
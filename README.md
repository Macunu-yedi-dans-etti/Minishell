# 🐚 Minishell - 42 School Projesi

## 📖 Proje Tanımı

Bu proje, Bash'e benzer bir kabuk (shell) oluşturmayı amaçlar. Kullanıcıdan komut alır, bu komutları işler ve işletim sistemi üzerinden yürütür. Program, çeşitli yerleşik (built-in) komutları ve sistem çağrılarını desteklemelidir.

## 📋 Hızlı Başlangıç

### 🚀 Derleme ve Çalıştırma
```bash
# Projeyi derle
make

# Minishell'i başlat
./minishell

# İlk komutunu dene
guest@minishell $ echo "Merhaba Dünya!"
```

### 📚 Dokümantasyon
Bu proje kapsamlı Türkçe dokümantasyona sahiptir:

- **🇹🇷 [Ana Türkçe Dokümantasyon](TURKCE_DOKUMANTASYON.md)** - Görsel diyagramlarla detaylı açıklama
- **🧪 [Görsel Test Senaryoları](GORSEL_TEST_SENARYOLARI.md)** - Test örnekleri ve diyagramlar
- **🚀 [Hızlı Kurulum Rehberi](HIZLI_KURULUM_REHBERI.md)** - Adım adım kurulum
- **📊 [Teknik Analiz](TECHNICAL_ANALYSIS.md)** - İngilizce teknik detaylar
- **📄 [PDF Alternatifleri](PDF_ALTERNATIFLERI.md)** - PDF oluşturma yöntemleri

### 📄 PDF Oluşturma

#### 🐧 Linux/macOS:
```bash
# Pandoc ile (önerilen)
./generate_pdf.sh

# VS Code ile (alternatif)
./vscode_pdf.sh
```

#### 🪟 Windows:
```powershell
# PowerShell ile
.\generate_pdf.ps1

# Veya VS Code Markdown PDF extension kullanın
```

**Pandoc kurulu değilse:** [PDF Alternatifleri](PDF_ALTERNATIFLERI.md) dosyasını okuyun.

---

## Zorunlu Özellikler

### 1. Prompt
- Her komutun başında yeni bir satırda prompt yazdırılmalı.
- `readline()` kullanılmalı.
- Ctrl+C ve Ctrl+\ gibi sinyaller doğru yönetilmeli.

### 2. Komutlar
#### External komutlar
- `ls`, `grep`, `cat` gibi binary komutları `execve()` kullanarak çalıştırmalısın.
- `PATH` değişkeni içinde arama yapılmalı.

#### Built-in komutlar
- `echo [-n] arg...`
- `cd [dir]`
- `pwd`
- `export [KEY=VALUE]`
- `unset KEY`
- `env`
- `exit [status]`

### 3. Redirections
- `< file` : dosyadan okuma
- `> file` : dosyaya yazma (üzerine yazar)
- `>> file` : dosyaya ekleme (append)
- `<< limiter` : heredoc

### 4. Pipes
- `ls | wc -l` gibi komutları desteklemeli.
- Her pipe bir `fork()` ve `dup2()` ile oluşturulmalı.

### 5. Quotes
- `'` ve `"` çiftleri içinde yazılan ifadeler düzgün ayıklanmalı.
- `$` ile başlayan değişkenler doğru şekilde yorumlanmalı.

### 6. Environment Değişkenleri
- `$HOME`, `$USER`, `$?`, `$PATH` gibi değişkenler desteklenmeli.
- `$?` son komutun çıkış kodunu içermeli.

---

## Yasaklı Fonksiyonlar

- `system()`
- `popen()`, `pclose()`
- `tmpfile()`, `tmpnam()`

---

## Kullanılacak Fonksiyonlar

```c
fork()
execve()
wait(), waitpid()
open(), close(), read(), write()
dup(), dup2()
pipe()
access()
isatty(), ttyname(), tcgetattr()
getcwd()
chdir()
getenv(), setenv(), unsetenv()
signal(), kill()
strtok(), strchr(), strdup(), malloc(), free()
```

---

## Kurulum

```bash
git clone https://github.com/kullanici/minishell.git
cd minishell
make
```

---

## Önerilen Klasör Yapısı

```
minishell/
├── src/
│   ├── main.c
│   ├── parser/
│   ├── executor/
│   ├── builtins/
│   ├── redirections/
│   └── signals/
├── include/
│   └── minishell.h
├── libft/
├── Makefile
```

---

## Test Edilecek Komutlar

```bash
echo hello world
echo -n test
pwd
cd ..
cd -
export VAR=value
echo $VAR
unset VAR
ls | grep minishell
cat < input.txt
ls > output.txt
ls >> output.txt
cat << EOF
merhaba
EOF
```

---

## Faydalı Komutlar ve Kütüphaneler

### readline kurulumu
```bash
brew install readline
```

### readline için derleme komutu
```makefile
-lreadline -lhistory
```

### valgrind ile test
```bash
valgrind --leak-check=full ./minishell
```

---

## Kaynaklar

- [man bash](https://man7.org/linux/man-pages/man1/bash.1.html)
- `man fork`, `man execve`, `man waitpid`, `man pipe`, `man dup2`, `man signal`
- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Creating a Shell in C (brennan.io)](https://brennan.io/2020/01/16/write-a-shell-in-c/)
- [Awesome Shell Resources](https://github.com/alebcay/awesome-shell)

---

## Notlar

- Her komut için yeni bir child process açmak gerekmez. Built-in komutlar parent içinde çalıştırılmalı.
- Her pipe aşaması için ayrı process ve pipe bağlantısı kurulmalı.
- Quote ve environment parsing ayrı ayrı işlenmeli.
- Segfault ya da memory leak olmamalı.

---

## Bonus (zorunlu değil)

- `&&` ve `||` desteği
- Wildcard (`*`) desteği
- Autocompletion
- Komut geçmişi dosyasına kayıt

---

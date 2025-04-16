# 🧩 minishell - Görev Tanımları

Bu dosyada `minishell` projesi için gerekli olan tüm görevlerin tanımı, alt görevleri, kabul kriterleri ve etiketleri yer almaktadır.

---

## 🧱 GÖREV: Kullanıcı girdisi alma ve prompt oluşturma

**Açıklama:**  
Kullanıcının terminalde girdiği komutları `readline()` ile alma. Boş satırda prompt tekrar gösterilmeli. Ctrl+D ile çıkış yapılmalı.

**Alt Görevler:**
- [ ] `readline()` ile input alma
- [ ] Boş inputta tekrar prompt göster
- [ ] Input’u history’ye ekle
- [ ] Ctrl+D yakalanarak program kapatılsın

**Kabul Kriterleri:**
- `readline` düzgün input alıyor
- Boşluk girildiğinde shell çökmüyor
- Ctrl+D ile normal çıkış yapılabiliyor

**Etiketler:** `input`, `prompt`, `readline`, `terminal`

---

## 🧠 GÖREV: Tokenizer ile input'u parçalara ayırma

**Açıklama:**  
Komutu kelime kelime ayırarak komutları, argümanları, quote’ları koruyarak parse edecek tokenizer sistemi kurulmalı.

**Alt Görevler:**
- [ ] Token bazlı ayırma fonksiyonu
- [ ] `'` ve `"` içindeki boşlukları koru
- [ ] `\` karakteriyle kaçışları işleme
- [ ] Token linked list’i oluştur

**Kabul Kriterleri:**
- Tırnak içindeki kelimeler ayrılmadan alınır
- Kaçış karakterleri doğru çalışır
- Token listesi sıralı oluşur

**Etiketler:** `parser`, `tokenizer`, `quote`, `input`

---

## 🔧 GÖREV: Redirection sembollerini parse etme

**Açıklama:**  
Komut satırındaki `<`, `>`, `>>`, `<<` gibi yönlendirme sembollerini komutlardan ayrıştır.

**Alt Görevler:**
- [ ] Redirection sembollerini yakala
- [ ] Her sembol için ayrı token türü belirle
- [ ] Redirection hedeflerini eşle

**Kabul Kriterleri:**
- Her redirection tipi tanınıyor
- Heredoc input’u alınabiliyor
- Komut ve dosya doğru eşleşiyor

**Etiketler:** `parser`, `redirect`, `heredoc`

---

## 🔀 GÖREV: Syntax kontrol sistemi oluştur

**Açıklama:**  
Kullanıcının yazdığı input’un syntax hatalarını kontrol eden bir yapı kurulmalı.

**Alt Görevler:**
- [ ] Boş input ve hatalı sembolleri tespit et
- [ ] `||`, `&&`, `;;;` gibi hatalı kullanımları kontrol et
- [ ] Uyarı ve hata mesajlarını bas

**Kabul Kriterleri:**
- Komut öncesi/sonrası pipe kontrolü yapılır
- Hatalı yazımlar hatasız şekilde yakalanır
- Shell çökmeksizin uyarı verir

**Etiketler:** `syntax`, `validation`, `parser`

---

## ⚙️ GÖREV: Executor ile komutları çalıştırma

**Açıklama:**  
Parse edilen komutları `fork()` ve `execve()` ile çalıştıracak bir yürütücü sistem yazılmalı.

**Alt Görevler:**
- [ ] Fork ile child process oluştur
- [ ] Execve ile binary çalıştır
- [ ] Parent process beklemeli (wait)

**Kabul Kriterleri:**
- `ls`, `echo`, `wc` gibi dış komutlar çalışıyor
- Komut sonrası terminal kontrolü geri dönüyor
- Çıkış kodları shell durumuna aktarılıyor

**Etiketler:** `executor`, `execve`, `fork`, `wait`

---

## 🔁 GÖREV: Pipe desteği

**Açıklama:**  
`|` sembolü ile birbirine bağlı komutların çıktı/girdi zincirini yöneten sistem kurulmalı.

**Alt Görevler:**
- [ ] Komutlar arası pipe bağlantısı kur
- [ ] `pipe()` ve `dup2()` ile fd yönlendirmesi yap
- [ ] Tüm pipe zinciri için child oluştur

**Kabul Kriterleri:**
- `cat file | grep hello` çalışıyor
- Birden fazla `|` destekleniyor
- Input/output sıralaması doğru

**Etiketler:** `pipe`, `dup2`, `fd`, `executor`

---

## 📁 GÖREV: Environment değişkenlerini yönetme

**Açıklama:**  
`env` değişkenleri başlangıçta alınmalı. Linked list formatında saklanmalı. `getenv`, `setenv`, `unsetenv` gibi erişim fonksiyonları yazılmalı.

**Alt Görevler:**
- [ ] Başlangıçta `envp`'den liste oluştur
- [ ] Env değişkeni ekleme/silme işlemleri
- [ ] Listeyi array’e dönüştürme fonksiyonu

**Kabul Kriterleri:**
- `env` çıktısı doğru gösteriliyor
- `export`, `unset` ile değişiklik yapılabiliyor
- Bellek sızıntısı olmuyor

**Etiketler:** `env`, `linkedlist`, `memory`

---

## 🔨 GÖREV: Built-in komutları yazma

**Açıklama:**  
Aşağıdaki komutlar shell içinde `execve` kullanılmadan doğrudan C ile implemente edilmeli:

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

**Alt Görevler:**
- [ ] Her komut için bir fonksiyon yaz
- [ ] `export` sonrası `env` güncelle
- [ ] `exit` ile düzgün çıkış yap

**Kabul Kriterleri:**
- Built-in komutlar çalışıyor
- Parametre kontrolleri doğru
- Bellek sızıntısı yok

**Etiketler:** `builtin`, `commands`, `env`, `shell`

---

## 🚨 GÖREV: Sinyal (signal) yönetimi

**Açıklama:**  
`SIGINT`, `SIGQUIT`, `EOF` gibi sinyallere özel davranışlar tanımlanmalı. Prompt ve child işlemler düzgün yanıt vermeli.

**Alt Görevler:**
- [ ] Prompt için Ctrl+C işleme
- [ ] Heredoc sırasında Ctrl+C işleme
- [ ] Ctrl+\ (SIGQUIT) için özel davranış

**Kabul Kriterleri:**
- Ctrl+C prompt’u bozmaz
- Heredoc ortasında Ctrl+C çıkış yapar
- Ctrl+\ ile shell çökmüyor

**Etiketler:** `signal`, `ctrlc`, `prompt`

---

## 🧪 GÖREV: Bellek yönetimi ve sızıntı testi

**Açıklama:**  
Tüm input, token, env ve execution yapılarına ait bellek doğru biçimde `free()` edilmelidir. `valgrind` temiz çıkmalı.

**Alt Görevler:**
- [ ] Tüm struct’lar için free fonksiyonları yaz
- [ ] Her hata durumunda memory temizlenmeli
- [ ] Testlerde `valgrind` uygulanmalı

**Kabul Kriterleri:**
- `valgrind` çıktısı clean
- Tek bir satırlık sızıntı yok
- Her işlem sonrası cleanup var

**Etiketler:** `memory`, `valgrind`, `leak`, `free`

---

## 📋 GÖREV: Exit status yönetimi

**Açıklama:**  
Çalışan her komuttan dönen çıkış kodu `$?` üzerinden yönetilmeli. Bu değer doğru saklanmalı ve erişilebilir olmalı.

**Alt Görevler:**
- [ ] Son komutun çıkış kodunu al
- [ ] Global değişkenle sakla
- [ ] `$?` yazıldığında göster

**Kabul Kriterleri:**
- Hatalı komut sonrası `$?` ≠ 0
- Başarılı komutta `$?` = 0
- Exit status güncel tutuluyor

**Etiketler:** `status`, `exitcode`, `$?`

---

## 🔚 GÖREV: minishell'den çıkış

**Açıklama:**  
Kullanıcı `exit` komutu girdiğinde veya Ctrl+D yaptığında minishell düzgün şekilde kapanmalı. Gerekli cleanup yapılmalı.

**Alt Görevler:**
- [ ] `exit` komutu parse edilir
- [ ] Cleanup fonksiyonu çağrılır
- [ ] Exit kodu atanır

**Kabul Kriterleri:**
- `exit` sonrası program kapanıyor
- Bellek sızıntısı yok
- `exit 42` gibi argümanlar doğru çalışıyor

**Etiketler:** `exit`, `builtin`, `cleanup`, `status`

---


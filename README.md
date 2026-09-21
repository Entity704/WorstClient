![DDraceNetwork](./data/gui_logo.png)

# wOrStClIeNt / 最爛客戶端 / WorstClient

**ThE wOrSt DDNeT cLiEnT.**

This rEaDmE is InTeNtIoNaLlY wOrSt: 18 languages, random camelCase, random 简繁 mixing.
重點只有一件事：**這個客卢端真正「拿得出手」的功能只有兩個。**
其他 UI 抖動 / shader glitch / 錯誤的 π …… 都是 branding，不是 feature。

---

## cOnFiG cHeAt ShEeT / 設定速查

| Config | Default | What it does |
|--------|---------|--------------|
| `wc_finish_protection` | `0` | 通關保護：有通関風險時自動 kill |
| `wc_show_off` | `0` | 炫耀：聊天自動追加 ` ... I use WorstClient btw` |
| console `wc_finish_protection_debug` | — | 打印通關保護當前狀態 |

Settings file: **`settings_worstclient.cfg`**
Open path: **Settings → WorstClient → Settings file**
(與 DDNet 的 `settings_ddnet.cfg` 分離，`wc_*` 变量都写在這裡。)

---

## 01 · English — ThE TwO fEaTuReS

WorstClient is a joke fork of DDNet. Despite the broken visuals, it ships **exactly two real client features**.

### 1. Finish Protection (`wc_finish_protection`)

**Auto-suicide when you are about to finish a race.**

While a race is running online (not demo / not spectator), the client:

1. Caches every finish tile (`TILE_FINISH`) on map load (game layer + front layer).
2. Measures distance from your predicted tee to the closest finish tile.
3. If distance **&lt; 32 units** → you are at risk.
4. If distance **&lt; 256 units**, it also **simulates your predicted tee for the next 10 ticks** and checks the same 5-point finish sampling the DDNet server uses.
5. When at risk, it executes `kill` **and** `say /kill`.
6. Frozen tees are not killed repeatedly; one kill per risk window.

Debug: type `wc_finish_protection_debug` in console.

UI string: *Finish Protection (auto suicide when at risk of finishing)*

### 2. Show Off (`wc_show_off`)

**Append a brag suffix to every chat message.**

- Outgoing chat becomes: `your message ... I use WorstClient btw`
- Chat **commands** starting with `/` (e.g. `/pause`, `/save`) are **never modified**.
- If the suffix does not fit the chat buffer, **nothing is appended** (original message is never truncated).
- Works on both 0.6 and 0.7 (Sixup) protocols.

UI string: *Show off (append " ... I use WorstClient btw" to chat messages)*

### How to enable

Settings → **WorstClient** tab → checkboxes. Or console:

```
wc_finish_protection 1
wc_show_off 1
```

---

## 02 · 中文（隨機簡繁）— 僅有的兩嗰功能

WorstClIeNt 是 DDNet 的 fork，README 故意寫得很爛。
真正在用的功能 **只有兩個**（當然只有兩個）。

### 1. 通關保護 / 通关保护（`wc_finish_protection`）

**有通関风险时自動自殺，避免誤触終點。**

仅在「線上比賽進行中」生效（回放、旁觀不觸發）：

- 加載地圖時缓存所有 `TILE_FINISH`（game layer + front layer）
- 計算預測 Tee 到最近終點图块的距離
- 距離 **&lt; 32 單位** → 判定為危險
- 若距離 **&lt; 256**，再用本地預測角色 **模擬 10 tick**，按 DDNet 服務器同款 5 點采樣判断是否會碰到終點
- 触发后執行 `kill` + `say /kill`
- 冰凍中的 Tee 不會被反覆擊殺；同一風險窗口只殺一次

調試指令：`wc_finish_protection_debug`

設置文案：*Finish Protection (auto suicide when at risk of finishing)* / 通關保護（有通關的風險時自動自殺）

### 2. 炫耀信息 / Show Off（`wc_show_off`）

**在每條聊天末尾自动追加炫耀後綴。**

- 發出的消息會变成：`你打的字 ... I use WorstClient btw`
- 以 `/` 開頭的指令（`/pause`、`/save` 等）**完全不動**
- 後綴放不下時 **整條不追加**，絕不截斷原文
- 兼容 0.6 / 0.7（Sixup）協議

設置文案：*Show off（在末尾追加「 ... I use WorstClient btw」）*

### 怎麼打開

設置 → **WorstClient** 頁簽，或控制台：

```
wc_finish_protection 1
wc_show_off 1
```

配置写入 `settings_worstclient.cfg`。

---

## 03 · 日本語 — たった2つの機能

WorstClient は DDNet のジョーク fork です。見た目は壊れていますが、**実用機能は2つだけ**です。

### 1. Finish Protection / クリア保護（`wc_finish_protection`）

**レース中にクリアしそうになったら自動で kill します。**

オンラインのレース中のみ動作（デモ・観戦では無効）:

- マップ読み込み時に `TILE_FINISH`（ゲームレイヤー＋フロントレイヤー）をキャッシュ
- 予測 Tee から最も近い終了タイルまでの距離を測定
- 距離 **32 ユニット未満** → 危険と判定
- 距離 **256 未満** なら、予測 Tee を **10 tick 先までシミュレート**（サーバーと同じ5点サンプリング）
- 危険時に `kill` と `say /kill` を実行
- 凍結中は連続 kill しない

デバッグ: `wc_finish_protection_debug`

### 2. Show Off（`wc_show_off`）

**チャットに自慢サフィックスを付けます。**

- 送信内容: `メッセージ ... I use WorstClient btw`
- `/` で始まるコマンドは **変更しない**
- サフィックスが入らない場合は **何も付けない**（切り捨てない）
- 0.6 / 0.7 両対応

有効化: 設定 → **WorstClient** タブ、または `wc_finish_protection 1` / `wc_show_off 1`

---

## 04 · 한국어 — 딱 두 가지 기능

WorstClient는 DDNet의 장난스러운 fork입니다. 화면은 엉망이지만, **실제 기능은 정확히 두 가지**입니다.

### 1. Finish Protection / 완주 보호 (`wc_finish_protection`)

**레이스 중 골에 근접하면 자동으로 kill 합니다.**

온라인 레이스 중에만 동작 (데모/관전 제외):

- 맵 로드 시 `TILE_FINISH` 좌표를 캐시
- 예측된 Tee에서 가장 가까운 골 타일까지 거리 측정
- 거리 **&lt; 32 유닛** → 위험 판단
- 거리 **&lt; 256** 이면 예측 Tee를 **10 tick 시뮬레이션** (서버와 동일한 5점 샘플링)
- 위험 시 `kill` + `say /kill` 실행
- 동결 상태에서 반복 kill 하지 않음

디버그: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**채팅에 자랑 접미사를 붙입니다.**

- 전송 내용: `메시지 ... I use WorstClient btw`
- `/` 로 시작하는 명령은 **변경하지 않음**
- 접미사가 들어가지 않으면 **아무것도 붙이지 않음**
- 0.6 / 0.7 모두 지원

설정 → **WorstClient** 탭, 또는 콘솔에서 `wc_finish_protection 1`, `wc_show_off 1`

---

## 05 · Français — SeUlEmEnT dEux fOnCtIoNs

WorstClient est un fork « pourri » de DDNet. L’UI tremble exprès, mais **il n’y a que deux vraies fonctionnalités**.

### 1. Finish Protection / Protection anti-finish (`wc_finish_protection`)

**Suicide automatique quand vous risquez de finir la course.**

Uniquement en ligne, course en cours (pas démo / pas spectateur):

- Cache toutes les tuiles `TILE_FINISH` au chargement de la carte
- Distance tee prédit → finish le plus proche
- Distance **&lt; 32 unités** → risque
- Si distance **&lt; 256**, simulation **10 ticks** du tee prédit (même échantillonnage 5 points que le serveur DDNet)
- Exécute `kill` + `say /kill`
- Pas de kill en boucle si le tee est gelé

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Ajoute un suffixe de frime à chaque message.**

- Message envoyé: `votre texte ... I use WorstClient btw`
- Les commandes `/` **ne sont jamais modifiées**
- Si le suffixe ne rentre pas, **rien n’est ajouté** (pas de troncature)
- Compatible 0.6 / 0.7

Réglages → onglet **WorstClient**, ou console `wc_finish_protection 1` / `wc_show_off 1`

---

## 06 · Deutsch — NuR ZwEi FeAtUrEs

WorstClient ist ein absichtlich schlechter DDNet-Fork. Die UI zittert, aber **echte Features gibt es genau zwei**.

### 1. Finish Protection / Finish-Schutz (`wc_finish_protection`)

**Automatischer Suizid, wenn du das Rennen beenden würdest.**

Nur online im laufenden Rennen (kein Demo / kein Zuschauer):

- Cacht alle `TILE_FINISH`-Kacheln beim Kartenladen
- Entfernung vorhergesagter Tee → nächstes Finish
- Distanz **&lt; 32 Einheiten** → Risiko
- Bei Distanz **&lt; 256** wird der Tee **10 Ticks simuliert** (gleiche 5-Punkt-Sampling wie der DDNet-Server)
- Führt `kill` + `say /kill` aus
- Eingefrorene Tees werden nicht dauerhaft gekillt

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Hängt einen Angeber-Suffix an jeden Chat.**

- Gesendet: `deine Nachricht ... I use WorstClient btw`
- `/`-Befehle **bleiben unangetastet**
- Passt der Suffix nicht, wird **nichts angehängt**
- 0.6 / 0.7 kompatibel

Einstellungen → Tab **WorstClient**, oder Konsole `wc_finish_protection 1` / `wc_show_off 1`

---

## 07 · Español — SoLo DoS fUnCiOnEs

WorstClient es un fork «malo a propósito» de DDNet. La UI tiembla, pero **solo hay dos funciones reales**.

### 1. Finish Protection / Protección anti-finish (`wc_finish_protection`)

**Suicidio automático si estás a punto de terminar la carrera.**

Solo online, carrera en curso (no demo / no espectador):

- Cachea todas las `TILE_FINISH` al cargar el mapa
- Distancia del tee predicho al finish más cercano
- Distancia **&lt; 32 unidades** → riesgo
- Si distancia **&lt; 256**, simula el tee **10 ticks** (muestreo de 5 puntos como el servidor)
- Ejecuta `kill` + `say /kill`
- No mata en bucle si el tee está congelado

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Añade un sufijo de arrogancia al chat.**

- Mensaje: `tu texto ... I use WorstClient btw`
- Los comandos `/` **no se modifican**
- Si no cabe el sufijo, **no se añade nada**
- Compatible 0.6 / 0.7

Ajustes → pestaña **WorstClient**, o consola `wc_finish_protection 1` / `wc_show_off 1`

---

## 08 · Português — ApEnAs DuAs fUnÇõEs

WorstClient é um fork propositalmente horrível do DDNet. A UI treme, mas **há exatamente duas funções reais**.

### 1. Finish Protection / Proteção anti-finish (`wc_finish_protection`)

**Suicídio automático quando você está prestes a completar a corrida.**

Só online, corrida em andamento (não demo / não espectador):

- Cacheia todos os `TILE_FINISH` ao carregar o mapa
- Distância do tee previsto até o finish mais próximo
- Distância **&lt; 32 unidades** → risco
- Se distância **&lt; 256**, simula o tee por **10 ticks** (mesma amostragem de 5 pontos do servidor)
- Executa `kill` + `say /kill`
- Não mata em loop se o tee estiver congelado

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Acrescenta um sufixo de exibicionismo ao chat.**

- Mensagem: `seu texto ... I use WorstClient btw`
- Comandos `/` **não são alterados**
- Se o sufixo não couber, **nada é adicionado**
- Compatível com 0.6 / 0.7

Configurações → aba **WorstClient**, ou console `wc_finish_protection 1` / `wc_show_off 1`

---

## 09 · Русский — ToLkO двE фyнкции

WorstClient — намеренно плохой форк DDNet. UI трясётся, но **реальных функций ровно две**.

### 1. Finish Protection / Защита от финиша (`wc_finish_protection`)

**Автоматический kill, если вы вот-вот финишируете.**

Только онлайн, гонка идёт (не демо / не наблюдатель):

- Кэширует все `TILE_FINISH` при загрузке карты
- Расстояние от предсказанного tee до ближайшего финиша
- Дистанция **&lt; 32 единиц** → риск
- Если **&lt; 256**, tee **симулируется на 10 тиков** (5-точечная выборка как на сервере)
- Выполняет `kill` + `say /kill`
- Замороженных tee не убивает повторно

Отладка: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Добавляет суффикс хвастовства в чат.**

- Сообщение: `ваш текст ... I use WorstClient btw`
- Команды `/` **не изменяются**
- Если суффикс не влезает — **ничего не добавляется**
- Поддержка 0.6 / 0.7

Настройки → вкладка **WorstClient**, или консоль `wc_finish_protection 1` / `wc_show_off 1`

---

## 10 · Italiano — SoLo DuE fUnZiOnI

WorstClient è un fork «peggiore apposta» di DDNet. La UI trema, ma **le funzioni vere sono solo due**.

### 1. Finish Protection / Protezione finish (`wc_finish_protection`)

**Suicidio automatico se stai per finire la corsa.**

Solo online, corsa in corso (niente demo / spettatore):

- Cache di tutte le `TILE_FINISH` al caricamento mappa
- Distanza tee predetto → finish più vicino
- Distanza **&lt; 32 unità** → rischio
- Se **&lt; 256**, simula il tee per **10 tick** (stesso campionamento a 5 punti del server)
- Esegue `kill` + `say /kill`
- Non killa a ripetizione se il tee è congelato

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Aggiunge un suffisso di vanto a ogni chat.**

- Messaggio: `il tuo testo ... I use WorstClient btw`
- I comandi `/` **non vengono toccati**
- Se il suffisso non sta, **non si aggiunge nulla**
- Compatibile 0.6 / 0.7

Impostazioni → scheda **WorstClient**, o console `wc_finish_protection 1` / `wc_show_off 1`

---

## 11 · Nederlands — MaAr TwEe FeAtUrEs

WorstClient is een bewust slechte DDNet-fork. De UI trilt, maar **er zijn precies twee echte functies**.

### 1. Finish Protection (`wc_finish_protection`)

**Automatische zelfmoord als je de race bijna uitloopt.**

Alleen online, race loopt (geen demo / geen toeschouwer):

- Cached alle `TILE_FINISH`-tegels bij mapload
- Afstand voorspelde tee → dichtstbijzijnde finish
- Afstand **&lt; 32 eenheden** → risico
- Bij **&lt; 256** wordt de tee **10 ticks gesimuleerd** (zelfde 5-punts sampling als de server)
- Voert `kill` + `say /kill` uit
- Bevroren tees niet herhaaldelijk killen

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Voegt een opschepperig suffix toe aan chat.**

- Bericht: `jouw tekst ... I use WorstClient btw`
- `/`-commando’s **worden niet aangepast**
- Past het suffix niet, dan **wordt er niets toegevoegd**
- Compatibel met 0.6 / 0.7

Instellingen → tab **WorstClient**, of console `wc_finish_protection 1` / `wc_show_off 1`

---

## 12 · Polski — tYlKo dWiE fUnKcJe

WorstClient to celowo zły fork DDNet. UI się trzęsie, ale **prawdziwych funkcji są tylko dwie**.

### 1. Finish Protection / Ochrona przed finishem (`wc_finish_protection`)

**Automatyczne samobójstwo, gdy zaraz skończysz wyścig.**

Tylko online, wyścig trwa (nie demo / nie widz):

- Cache wszystkich `TILE_FINISH` przy wczytaniu mapy
- Odległość przewidywanego tee → najbliższy finish
- Odległość **&lt; 32 jednostek** → ryzyko
- Gdy **&lt; 256**, tee jest **symulowany przez 10 ticków** (5-punktowe próbkowanie jak na serwerze)
- Wykonuje `kill` + `say /kill`
- Zamrożonych tee nie zabija w kółko

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Dodaje sufiks chwalenia się do czatu.**

- Wiadomość: `twoj tekst ... I use WorstClient btw`
- Komendy `/` **nie są zmieniane**
- Jeśli sufiks się nie mieści — **nic nie jest dodawane**
- Kompatybilne z 0.6 / 0.7

Ustawienia → zakładka **WorstClient**, lub konsola `wc_finish_protection 1` / `wc_show_off 1`

---

## 13 · Türkçe — YaLnİzCa İKi ÖZellİk

WorstClient, DDNet’in kasıtlı olarak berbat bir fork’udur. UI titriyor ama **gerçek özellik sadece iki tane**.

### 1. Finish Protection / Bitiş koruması (`wc_finish_protection`)

**Yarışı bitirmek üzereysen otomatik kill.**

Sadece çevrimiçi, yarış sürerken (demo / izleyici değil):

- Harita yüklenirken tüm `TILE_FINISH` kareleri önbelleğe alınır
- Tahmini tee → en yakın bitiş mesafesi
- Mesafe **&lt; 32 birim** → risk
- **&lt; 256** ise tee **10 tick simüle** edilir (sunucuyla aynı 5 nokta örnekleme)
- `kill` + `say /kill` çalıştırır
- Donmuş tee’yi tekrar tekrar kill etmez

Hata ayıklama: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Sohbete övünme soneki ekler.**

- Mesaj: `yazın ... I use WorstClient btw`
- `/` ile başlayan komutlar **değiştirilmez**
- Sonek sığmazsa **hiçbir şey eklenmez**
- 0.6 / 0.7 uyumlu

Ayarlar → **WorstClient** sekmesi, veya konsol `wc_finish_protection 1` / `wc_show_off 1`

---

## 14 · العربية — وظيفتان فقط

WorstClient هو fork متعمّد السيئة لـ DDNet. الواجهة تهتزّ عمدًا، لكن **الوظائف الحقيقية اثنتان فقط**.

### 1. Finish Protection / حماية النهاية (`wc_finish_protection`)

**انتحار تلقائي عندما تكون على وشك إنهاء السباق.**

يعمل فقط أونلاين أثناء السباق (لا демо / لا متفرج):

- يخزّن كل مربعات `TILE_FINISH` عند تحميل الخريطة
- المسافة من tee المتوقّع إلى أقرب نهاية
- المسافة **&lt; 32 وحدة** → خطر
- إذا كانت **&lt; 256**، يُحاكى الـ tee لـ **10 ticks** (نفس أخذ العينات بخمس نقاط كالخادم)
- ينفّذ `kill` + `say /kill`
- لا يقتل tee المتجمّد مرارًا

التصحيح: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**يضيف لاحقة تباهٍ إلى الدردشة.**

- الرسالة: `نصك ... I use WorstClient btw`
- الأوامر التي تبدأ بـ `/` **لا تُعدَّل**
- إن لم تتّسع اللاحقة **لا يُضاف شيء**
- متوافق مع 0.6 / 0.7

الإعدادات → تبويب **WorstClient**، أو الكونسول `wc_finish_protection 1` / `wc_show_off 1`

---

## 15 · Tiếng Việt — Chỉ hAi ChỨc NăNG

WorstClient là fork DDNet cố tình tệ. UI rung là chủ đích, nhưng **chỉ có hai chức năng thật**.

### 1. Finish Protection / Bảo vệ về đích (`wc_finish_protection`)

**Tự kill khi bạn sắp hoàn thành chặng đua.**

Chỉ chạy online, đua đang diễn ra (không demo / không khán giả):

- Cache mọi ô `TILE_FINISH` khi tải map
- Khoảng cách tee dự đoán → finish gần nhất
- Khoảng cách **&lt; 32 đơn vị** → nguy hiểm
- Nếu **&lt; 256**, mô phỏng tee **10 tick** (lấy mẫu 5 điểm như server)
- Thực thi `kill` + `say /kill`
- Không kill lặp khi tee đang đóng băng

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Thêm hậu tố khoe khoang vào chat.**

- Tin nhắn: `của bạn ... I use WorstClient btw`
- Lệnh bắt đầu bằng `/` **không bị sửa**
- Nếu hậu tố không đủ chỗ thì **không thêm gì**
- Tương thích 0.6 / 0.7

Cài đặt → tab **WorstClient**, hoặc console `wc_finish_protection 1` / `wc_show_off 1`

---

## 16 · ไทย — ฟีเจอร์จริงแค่สองอย่าง

WorstClient คือ fork ของ DDNet ที่ตั้งใจให้ห่วย UI สั่นตามคอนเซปต์ แต่**ฟีเจอร์จริงมีแค่สองอย่าง**

### 1. Finish Protection / กันจบด่าน (`wc_finish_protection`)

**ฆ่าตัวตายอัตโนมัติเมื่อเสี่ยงจะจบเรซ**

ทำงานเฉพาะออนไลน์ ตอนเรซกำลังแข่ง (ไม่ใช่เดโม/ผู้ชม):

- แคช tile `TILE_FINISH` ตอนโหลดแมพ
- วัดระยะ tee ที่ทำนายไว้ ถึง finish ที่ใกล้สุด
- ระยะ **&lt; 32 หน่วย** → เสี่ยง
- ถ้า **&lt; 256** จะจำลอง tee **10 tick** (สุ่ม 5 จุดแบบเดียวกับเซิร์ฟเวอร์)
- รัน `kill` + `say /kill`
- ไม่ kill ซ้ำตอน tee ถูกแช่แข็ง

ดีบัก: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**ต่อท้ายแชทด้วยข้อความอวด**

- ข้อความ: `ของคุณ ... I use WorstClient btw`
- คำสั่งที่ขึ้นต้นด้วย `/` **จะไม่ถูกแก้**
- ถ้าต่อท้ายไม่พอ **จะไม่ต่ออะไรเลย**
- รองรับ 0.6 / 0.7

ตั้งค่า → แท็บ **WorstClient** หรือคอนโซล `wc_finish_protection 1` / `wc_show_off 1`

---

## 17 · Bahasa Indonesia — HaNya DuA FiTuR

WorstClient adalah fork DDNet yang sengaja dibuat jelek. UI bergetar itu fitur branding — **fungsi nyata cuma dua**.

### 1. Finish Protection / Perlindungan finish (`wc_finish_protection`)

**Bunuh diri otomatis saat kamu hampir menyelesaikan race.**

Hanya online, race sedang berjalan (bukan demo / penonton):

- Cache semua `TILE_FINISH` saat map load
- Jarak tee prediksi → finish terdekat
- Jarak **&lt; 32 unit** → berisiko
- Jika **&lt; 256**, tee disimulasikan **10 tick** (sampling 5 titik seperti server)
- Menjalankan `kill` + `say /kill`
- Tidak kill berulang saat tee beku

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Menambahkan akhiran pamer ke chat.**

- Pesan: `pesanmu ... I use WorstClient btw`
- Perintah berawalan `/` **tidak diubah**
- Jika akhiran tidak muat — **tidak ditambahkan apa pun**
- Kompatibel 0.6 / 0.7

Pengaturan → tab **WorstClient**, atau konsol `wc_finish_protection 1` / `wc_show_off 1`

---

## 18 · Ελληνικά — MoNo DyO LeitourgIes

Το WorstClient είναι σκόπιμα κακό fork του DDNet. Το UI τρέμει επίτηδες, αλλά **οι πραγματικές λειτουργίες είναι ακριβώς δύο**.

### 1. Finish Protection / Προστασία finish (`wc_finish_protection`)

**Αυτόματη αυτοκτονία όταν πρόκειται να τερματίσεις τον αγώνα.**

Μόνο online, ενώ τρέχει αγώνας (όχι demo / θεατής):

- Αποθηκεύει κάθε `TILE_FINISH` κατά το φόρτωση χάρτη
- Απόσταση προβλεπόμενου tee → πλησιέστερο finish
- Απόσταση **&lt; 32 μονάδες** → κίνδυνος
- Αν **&lt; 256**, ο tee **προσομοιώνεται 10 ticks** (ίδιο 5-point sampling με τον server)
- Εκτελεί `kill` + `say /kill`
- Δεν kill-άρει συνεχώς παγωμένο tee

Debug: `wc_finish_protection_debug`

### 2. Show Off (`wc_show_off`)

**Προσθέτει επίθημα επίδειξης στο chat.**

- Μήνυμα: `το κείμενό σου ... I use WorstClient btw`
- Οι εντολές `/` **δεν αλλάζουν**
- Αν δεν χωρεί το επίθημα — **δεν προστίθεται τίποτα**
- Συμβατό με 0.6 / 0.7

Ρυθμίσεις → καρτέλα **WorstClient**, ή κονσόλα `wc_finish_protection 1` / `wc_show_off 1`

---

## Building / 編譯 / Build（DDNet 同款）

Still a DDNet codebase. Same build story:

**Linux / macOS**

```sh
cmake -Bbuild -GNinja
cmake --build build
```

**Windows**: Visual Studio CMake integration, or MSVC build tools + CMake Tools.
Needs: C++ toolchain, Python 3, Rust.

Fork settings live in `settings_worstclient.cfg` after the main `settings_ddnet.cfg`.

---

## License

Same as upstream DDNet (see `license.txt`).

---

<sub>
本 README 故意混合簡繁與大小寫 — 因為這客户端叫 wOrStClIeNt。
功能只有兩個：Finish Protection + Show Off。其他都是 flavor。
</sub>

![DDraceNetwork](./data/gui_logo.png)

# wOrStClIeNt · 最爛クライアント · WorstClient

**ThE wOrSt DDNeT cLiEnT — этот клиент故意做爛，mais les vraies fonctions sont hanya dua.**

This README is mixed on purpose: almost every sentence blends **3+ of 18 languages**, with random camelCase and random 简繁. 功能重點只有兩個 — *nur zwei*, *たった二つ*, *hanya dua*, *فقط اثنتان*.

---

## cOnFiG / 設定 / Config

| key | default | meaning |
|-----|---------|---------|
| `wc_finish_protection` | `0` | 通關保護 / Finish Protection — 自動 kill wenn du dabei bist zu finishen |
| `wc_show_off` | `0` | 炫耀 / Show Off — chat 末尾追加 ` ... I use WorstClient btw` |
| `wc_finish_protection_debug` | console | debug: 印出当前 pelindungan finish 狀態 |

Settings file → **`settings_worstclient.cfg`**；open path → **Settings → WorstClient**（設定頁簽 / onglet / sekmе）。

---

## ThE TwO fEaTuReS · 僅有的兩嗰功能 · les deux seules fonctions

WorstClient は DDNet の joke fork です，**però ci sono solo due funzioni reali**，и их ровно две。

### 1. Finish Protection / 通關保護 / Clearrchutz

**Auto-suicide when you are about to finish — 有通関風險時自動自殺，lorsque vous risquez de terminer la course.**

While a race is running online（線上比賽進行中；pas en démo / nicht Spectator / 観戦では無効）:

1. 加載地圖時 cache todas las `TILE_FINISH` tiles — game layer + front layer 一起掃，**juntos con** front-layer。
2. 計算預測 Tee 到最近終點的距離 — *distance au finish le plus proche*, *Entfernung zum nächsten Finish*。
3. Wenn distance **&lt; 32 units / 32 單位 / 32 birim** → you are at risk, *estás en riesgo*, *вы в опасности*。
4. Si distance **&lt; 256**, client **simulates the predicted tee for 10 ticks / 模擬 10 tick / 10 ticks simulieren**，採用 DDNet 服務器同款 5-point sampling（5 點采樣 / fünf Punkte）。
5. Trigger 後執行 `kill` **ve** `say /kill` — *executes both*, *eksekusi keduanya*, *εκτελεί και τα δύο*。
6. 凍結 Tee 不會被反覆擊殺 — *frozen tees are not killed repeatedly*, *gelée tee ne tue pas en boucle*。

Debug console → `wc_finish_protection_debug`（印出 enabled / cached tiles / closest_finish / will_touch / at_risk / frozen）。

UI label（界面文案 / libellé）: *Finish Protection (auto suicide when at risk of finishing)* — 通關保護（有通關的風險時自動自殺）。

### 2. Show Off / 炫耀 / Se vanter

**Append a brag suffix to every chat — 每條聊天自動追加炫耀後綴，ajoute un suffixe de frime à chaque message.**

- 發出的消息会变成 / becomes / devient: `你打的字 ... I use WorstClient btw`
- 以 `/` 開頭的指令 **完全不動** — *commands like `/pause` are never modified*, *Befehle bleiben unangetastet*, *komutlar değiştirilmez*。
- 後綴放不下時 **整條不追加** — *if the suffix does not fit, nothing is appended*, *pas de troncature*, *não truncado*。
- 兼容 0.6 / 0.7（Sixup）協議 — *works on both protocols*, *compatible avec*, *0.6 / 0.7 uyumlu*。

UI label: *Show off（在末尾追加「 ... I use WorstClient btw」）*。

---

## HoW tO eNaBlE / 怎麼打開 / Comment activer

Settings → **WorstClient** 頁簽 / onglet / sekme / scheda → checkboxes（複選框 / cases à cocher）:

```
wc_finish_protection 1
wc_show_off 1
```

These `wc_*` variables are saved to **`settings_worstclient.cfg`**，與 `settings_ddnet.cfg` 分離 — *separated from upstream settings*, *getrennt von DDNet*, *ayrı dosyada saklanır*。

---

## MiXeD 18-LanGuAgE sAmPlEs（風格示例 / ejemplos / exemplos）

每句話混 3+ 語言 — *each sentence mixes three or more tongues*, *chaque phrase mélange*, *her cümle karışır*:

- Finish Protection 會 **aUtOmAtIcAlLy KiLl** your tee *wenn* vous êtes *sur le point de* terminar la carrera *y* el cliente envía `kill`。
- Show Off **aPpEnDs** suffix *mais* les commandes `/` *bleiben* untouched *e* il testo *no* viene *troncato*。
- 這個客卢端故意做爛 UI — *l’UI tremble exprès*, *UI は壊れています*, *UI kasıtlı bozuk* — **tapi fitur nyata cuma dua**。
- Config 檔案叫 `settings_worstclient.cfg`，*open it* via Settings → WorstClient — *öffne die Datei*, *ファイルを開く*, *dosyayı aç*。

---

## BuIlDiNg / 編譯 / Compilation

Still DDNet codebase — *même base de code*, *gleiche Codebasis*, *同じコードベース*:

```sh
cmake -Bbuild -GNinja
cmake --build build
```

Windows → Visual Studio CMake *ou* MSVC build tools；需要 C++ *et* Python 3 *y* Rust。

---

## 18 LaNgUaGeS uSeD / 使用的十八國語言

English · 中文（隨機簡繁）· 日本語 · 한국어 · Français · Deutsch · Español · Português · Русский · Italiano · Nederlands · Polski · Türkçe · العربية · Tiếng Việt · ไทย · Bahasa Indonesia · Ελληνικά

*Almost every sentence above mixes ≥3 of these* — 並隨機大小寫 / camelCase，中文隨機簡繁。

---

## License

Same as upstream DDNet — *voir* `license.txt`, *siehe*, *を参照*。

---

<sub>
本 README 故意一句混多語 + 隨機簡繁 + 隨機大小寫 — porque el cliente se llama **wOrStClIeNt**。
功能只有兩個：**Finish Protection** + **Show Off**。其他都是 flavor / 風味 / Geschmack。
</sub>

<?php
	// コンパイル済み住所データを読み込み、初期化
	dams_init();

	// デバッグ表示の設定
	dams_debugmode(false); // デフォルト値

	// 最大表示件数の設定
	dams_set_limit(10); // デフォルト値

	// 部分一致を検索しない住所レベルの設定
	dams_set_exact_match_level(5); // デフォルト値

	// 住所を検索	
	$result = dams_retrieve("駒場4-6-1");
	
	// 結果を表示
	printf("score=%d\n", $result->score);
	printf("tail=%s\n", $result->tail);
	$count = 0;
	foreach ($result->candidates as $candidate) {
		printf("candidates[%d]:\n", $count);
		foreach ($candidate as $element) {
			printf("  name=%s, level=%d, x=%f, y=%f\n", 
				$element->name, $element->level, $element->x, $element->y);
		}
		$count++;
	}

	printf("\n実行時間: %d（ミリ秒）\n", dams_elapsedtime());

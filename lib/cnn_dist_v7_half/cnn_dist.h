
#pragma once
extern "C" {
#include <cblas.h>
};

#include <cmath>

struct cnn_dist_v7 {
	const static int latency = 511;
	const static int MAX_L = MAX_BUFFER + latency;
	const static int MAX_CH = 4;
	// About 8e-06*(MAX_BUFFER+511) MB of buffer
	float x_even[MAX_L][MAX_CH];
	float x_odd [MAX_L][MAX_CH];

	void operator()(float* x, float* y, int L) {

		// Ensure we don't segfault
		L = L > MAX_L ? MAX_L : L;

		for (int i = 0; i < L; i++) {
			x_odd[i][0] = x[i];
		}

		// auto-generated code for layer layer_0: Conv1d(1, 4, kernel_size=(2,), stride=(1,), dilation=(512,))
		const float w_layer_0[2][1][4] = {{{-0.5470113158226013,-0.9956218600273132,-0.832747757434845,-0.32301515340805054}},{{0.7308305501937866,0.6734246611595154,-1.50735604763031,-1.362637996673584}}};
		const float b_layer_0[4] = {-0.013813343830406666,0.06653717905282974,0.13660050928592682,0.021740995347499847};

		// Fill with biases for layer_0
		for (int l = 256; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				x_even[l][i] = b_layer_0[i];
			}
		}

		// Apply main filter for layer_0
		// x_even[:,256:] = sum(w[k]@x_odd[:,256-(1-k)*256:L-(1-k)*256] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*256;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 4, L-256, 1, 1.0, &w_layer_0[k][0][0], 4, &x_odd[256-offset][0], MAX_CH, 1.0, &x_even[256][0], MAX_CH);
		}


		// Hard Tanh (i.e. hard clip)
		for (int l = 256; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				auto& v = x_even[i][l];
				x_even[l][i] = v > 1 ? 1 : v < -1 ? -1 : v;
			}
		}


		// auto-generated code for layer layer_1: Conv1d(4, 4, kernel_size=(2,), stride=(1,), dilation=(256,))
		const float w_layer_1[2][4][4] = {{{0.2192024439573288,1.0773683786392212,-0.21740390360355377,-0.8132020235061646},{0.28044646978378296,0.8257229924201965,-0.20419174432754517,-0.461124062538147},{-1.0429761409759521,-0.36531099677085876,0.5549978613853455,0.10685146600008011},{-0.4442256987094879,-0.3063925504684448,0.6491906046867371,-0.17902237176895142}},{{0.4084133505821228,-0.05422694981098175,0.04838316887617111,0.6146253943443298},{0.2835703492164612,0.27954599261283875,0.26998862624168396,1.2426304817199707},{0.30342960357666016,0.3633834719657898,0.6617127060890198,0.3653370440006256},{0.10381437093019485,-0.21275439858436584,-0.0167961735278368,0.20296484231948853}}};
		const float b_layer_1[4] = {0.11012754589319229,-0.014727044850587845,-0.1883411854505539,-0.16488218307495117};

		// Fill with biases for layer_1
		for (int l = 384; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				x_odd[l][i] = b_layer_1[i];
			}
		}

		// Apply main filter for layer_1
		// x_odd[:,384:] = sum(w[k]@x_even[:,384-(1-k)*128:L-(1-k)*128] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*128;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 4, L-384, 4, 1.0, &w_layer_1[k][0][0], 4, &x_even[384-offset][0], MAX_CH, 1.0, &x_odd[384][0], MAX_CH);
		}


		// Hard Tanh (i.e. hard clip)
		for (int l = 384; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				auto& v = x_odd[i][l];
				x_odd[l][i] = v > 1 ? 1 : v < -1 ? -1 : v;
			}
		}


		// auto-generated code for layer layer_2: Conv1d(4, 4, kernel_size=(2,), stride=(1,), dilation=(128,))
		const float w_layer_2[2][4][4] = {{{-0.8852570652961731,-0.07280974090099335,0.6929574012756348,0.24359126389026642},{-0.5896333456039429,-0.04348747432231903,0.3316805958747864,0.2925724387168884},{0.19034069776535034,-0.06111970171332359,-0.7788625359535217,0.15512686967849731},{-0.13784286379814148,-0.044831782579422,0.01061760913580656,-0.002551378682255745}},{{-0.03368068486452103,-0.4234389364719391,-1.35561203956604,-0.9563305377960205},{-0.49239251017570496,-0.2149629294872284,-0.8260172009468079,-0.27719825506210327},{0.20752909779548645,0.4464603662490845,0.9728422164916992,-0.019688010215759277},{0.05607236176729202,0.5057648420333862,0.47026562690734863,-0.364626407623291}}};
		const float b_layer_2[4] = {0.17193488776683807,0.10485821217298508,-0.32053419947624207,0.10791219025850296};

		// Fill with biases for layer_2
		for (int l = 448; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				x_even[l][i] = b_layer_2[i];
			}
		}

		// Apply main filter for layer_2
		// x_even[:,448:] = sum(w[k]@x_odd[:,448-(1-k)*64:L-(1-k)*64] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*64;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 4, L-448, 4, 1.0, &w_layer_2[k][0][0], 4, &x_odd[448-offset][0], MAX_CH, 1.0, &x_even[448][0], MAX_CH);
		}


		// Hard Tanh (i.e. hard clip)
		for (int l = 448; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				auto& v = x_even[i][l];
				x_even[l][i] = v > 1 ? 1 : v < -1 ? -1 : v;
			}
		}


		// auto-generated code for layer layer_3: Conv1d(4, 4, kernel_size=(2,), stride=(1,), dilation=(64,))
		const float w_layer_3[2][4][4] = {{{-0.31422385573387146,-0.14600083231925964,0.3035121560096741,0.3984229564666748},{-1.0321524143218994,0.21840554475784302,0.07303741574287415,-0.5484250783920288},{0.16498015820980072,-0.4728172719478607,-0.2709878385066986,-0.47379425168037415},{-0.48916834592819214,0.29659712314605713,-0.3355199992656708,-0.6498945355415344}},{{-0.20973999798297882,0.6666712164878845,0.19758303463459015,0.06946990638971329},{0.6795411109924316,0.08024068176746368,1.4868677854537964,0.10521149635314941},{0.18904909491539001,-0.04661424085497856,0.09788632392883301,-0.06430349498987198},{0.4678221642971039,0.898855447769165,0.2524047791957855,-0.5363168716430664}}};
		const float b_layer_3[4] = {0.21912811696529388,0.07621839642524719,0.04539365693926811,0.006204461678862572};

		// Fill with biases for layer_3
		for (int l = 480; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				x_odd[l][i] = b_layer_3[i];
			}
		}

		// Apply main filter for layer_3
		// x_odd[:,480:] = sum(w[k]@x_even[:,480-(1-k)*32:L-(1-k)*32] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*32;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 4, L-480, 4, 1.0, &w_layer_3[k][0][0], 4, &x_even[480-offset][0], MAX_CH, 1.0, &x_odd[480][0], MAX_CH);
		}


		// Hard Tanh (i.e. hard clip)
		for (int l = 480; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				auto& v = x_odd[i][l];
				x_odd[l][i] = v > 1 ? 1 : v < -1 ? -1 : v;
			}
		}


		// auto-generated code for layer layer_4: Conv1d(4, 4, kernel_size=(2,), stride=(1,), dilation=(32,))
		const float w_layer_4[2][4][4] = {{{0.0063829016871750355,0.00994156114757061,0.05215441435575485,1.5985556840896606},{-0.4130563735961914,-0.5328793525695801,0.11284594982862473,0.793258011341095},{-0.12560604512691498,-0.1601589322090149,0.8719216585159302,1.0731008052825928},{0.43596652150154114,-1.2759565114974976,0.5487668514251709,-0.4703928828239441}},{{0.14787249267101288,0.27533286809921265,-0.10624083131551743,1.4825161695480347},{-0.152329683303833,-0.4295813739299774,-0.040401313453912735,-0.35443437099456787},{0.3180423676967621,-0.14225274324417114,0.09992566704750061,-0.351047545671463},{0.08933503925800323,-0.5193877220153809,0.7331037521362305,0.8401932120323181}}};
		const float b_layer_4[4] = {0.0937061682343483,-0.591589093208313,0.1185731440782547,-0.10743146389722824};

		// Fill with biases for layer_4
		for (int l = 496; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				x_even[l][i] = b_layer_4[i];
			}
		}

		// Apply main filter for layer_4
		// x_even[:,496:] = sum(w[k]@x_odd[:,496-(1-k)*16:L-(1-k)*16] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*16;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 4, L-496, 4, 1.0, &w_layer_4[k][0][0], 4, &x_odd[496-offset][0], MAX_CH, 1.0, &x_even[496][0], MAX_CH);
		}


		// Hard Tanh (i.e. hard clip)
		for (int l = 496; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				auto& v = x_even[i][l];
				x_even[l][i] = v > 1 ? 1 : v < -1 ? -1 : v;
			}
		}


		// auto-generated code for layer layer_5: Conv1d(4, 4, kernel_size=(2,), stride=(1,), dilation=(16,))
		const float w_layer_5[2][4][4] = {{{-0.35319364070892334,0.353882759809494,-0.12483451515436172,-1.4875879287719727},{-0.30960404872894287,0.10336072742938995,-0.0629754364490509,-0.27698421478271484},{0.347435861825943,0.4783235490322113,-0.16128377616405487,-0.24497903883457184},{0.6355705261230469,0.09947893768548965,0.49170538783073425,0.21729376912117004}},{{-0.15221332013607025,0.05901329964399338,-0.4851718246936798,0.8887662887573242},{-0.05932115018367767,0.3377787470817566,0.1633574217557907,-0.28718018531799316},{-0.1503322720527649,0.2123149335384369,-0.4471210241317749,-0.38272523880004883},{-0.048329368233680725,-0.4874809980392456,0.06861048936843872,-1.2711329460144043}}};
		const float b_layer_5[4] = {0.15729105472564697,0.166515052318573,-0.4948497712612152,-0.3757469952106476};

		// Fill with biases for layer_5
		for (int l = 504; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				x_odd[l][i] = b_layer_5[i];
			}
		}

		// Apply main filter for layer_5
		// x_odd[:,504:] = sum(w[k]@x_even[:,504-(1-k)*8:L-(1-k)*8] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*8;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 4, L-504, 4, 1.0, &w_layer_5[k][0][0], 4, &x_even[504-offset][0], MAX_CH, 1.0, &x_odd[504][0], MAX_CH);
		}


		// Hard Tanh (i.e. hard clip)
		for (int l = 504; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				auto& v = x_odd[i][l];
				x_odd[l][i] = v > 1 ? 1 : v < -1 ? -1 : v;
			}
		}


		// auto-generated code for layer layer_6: Conv1d(4, 4, kernel_size=(2,), stride=(1,), dilation=(8,))
		const float w_layer_6[2][4][4] = {{{0.2037886083126068,-0.06579753011465073,0.16246065497398376,-0.11406321078538895},{0.1588311791419983,-0.49906808137893677,0.6505011320114136,0.5640144348144531},{0.2775684595108032,0.4214322865009308,-0.30392971634864807,-0.26688113808631897},{0.37061983346939087,-0.08714272081851959,-0.2593551278114319,0.11510904133319855}},{{0.12455328553915024,0.41211700439453125,0.12695245444774628,0.006463333498686552},{0.30003294348716736,0.36910465359687805,-0.24338100850582123,0.2423090636730194},{-0.2970002293586731,-0.15456251800060272,-0.35548141598701477,0.006600117310881615},{1.4171595573425293,0.5754849910736084,0.4090157449245453,-0.2891547977924347}}};
		const float b_layer_6[4] = {0.09222554415464401,-0.15123401582241058,0.3564896881580353,-0.20256847143173218};

		// Fill with biases for layer_6
		for (int l = 508; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				x_even[l][i] = b_layer_6[i];
			}
		}

		// Apply main filter for layer_6
		// x_even[:,508:] = sum(w[k]@x_odd[:,508-(1-k)*4:L-(1-k)*4] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*4;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 4, L-508, 4, 1.0, &w_layer_6[k][0][0], 4, &x_odd[508-offset][0], MAX_CH, 1.0, &x_even[508][0], MAX_CH);
		}


		// Hard Tanh (i.e. hard clip)
		for (int l = 508; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				auto& v = x_even[i][l];
				x_even[l][i] = v > 1 ? 1 : v < -1 ? -1 : v;
			}
		}


		// auto-generated code for layer layer_7: Conv1d(4, 4, kernel_size=(2,), stride=(1,), dilation=(4,))
		const float w_layer_7[2][4][4] = {{{-0.4395342171192169,0.22177940607070923,0.39254230260849,0.056675903499126434},{0.2816139757633209,0.4973168969154358,-0.053250838071107864,0.3442734181880951},{-0.3813002407550812,-0.04815910756587982,0.160305917263031,0.08043602108955383},{-0.2289036214351654,0.18205119669437408,0.1553620994091034,-0.14367526769638062}},{{0.09662049263715744,-0.9713948369026184,-0.3301687240600586,0.5227264761924744},{0.2203361839056015,-0.25315380096435547,-0.30136650800704956,0.1537085771560669},{0.2944323420524597,-0.045082032680511475,0.08527776598930359,0.4099138379096985},{-0.18521463871002197,0.3369217813014984,0.008049417287111282,-0.4629855155944824}}};
		const float b_layer_7[4] = {0.09610868245363235,-0.02362729050219059,-0.22199848294258118,0.2086700052022934};

		// Fill with biases for layer_7
		for (int l = 510; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				x_odd[l][i] = b_layer_7[i];
			}
		}

		// Apply main filter for layer_7
		// x_odd[:,510:] = sum(w[k]@x_even[:,510-(1-k)*2:L-(1-k)*2] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*2;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 4, L-510, 4, 1.0, &w_layer_7[k][0][0], 4, &x_even[510-offset][0], MAX_CH, 1.0, &x_odd[510][0], MAX_CH);
		}


		// Hard Tanh (i.e. hard clip)
		for (int l = 510; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				auto& v = x_odd[i][l];
				x_odd[l][i] = v > 1 ? 1 : v < -1 ? -1 : v;
			}
		}


		// auto-generated code for layer layer_8: Conv1d(4, 4, kernel_size=(2,), stride=(1,), dilation=(2,))
		const float w_layer_8[2][4][4] = {{{-0.1621023565530777,0.2489013969898224,0.20878495275974274,-0.4441147744655609},{-0.08744358271360397,-0.10556954890489578,0.4504779577255249,-0.2937629520893097},{0.14383535087108612,0.017578426748514175,-0.06892804056406021,0.18231476843357086},{-0.20978772640228271,-0.0009873297531157732,0.1802099347114563,0.010096161626279354}},{{-0.023611074313521385,-0.1021597683429718,-0.030623411759734154,0.0896734967827797},{0.3647127151489258,0.02266024425625801,-0.44709524512290955,0.28452423214912415},{0.1962222158908844,0.19618430733680725,-0.14073267579078674,-0.09239627420902252},{-0.05598657205700874,-0.05655395984649658,0.28450721502304077,-0.17221233248710632}}};
		const float b_layer_8[4] = {0.04878132417798042,0.008886340074241161,0.13395090401172638,0.12121317535638809};

		// Fill with biases for layer_8
		for (int l = 511; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				x_even[l][i] = b_layer_8[i];
			}
		}

		// Apply main filter for layer_8
		// x_even[:,511:] = sum(w[k]@x_odd[:,511-(1-k)*1:L-(1-k)*1] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*1;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 4, L-511, 4, 1.0, &w_layer_8[k][0][0], 4, &x_odd[511-offset][0], MAX_CH, 1.0, &x_even[511][0], MAX_CH);
		}


		// Hard Tanh (i.e. hard clip)
		for (int l = 511; l < L; l++) {
			for (int i = 0; i < 4; i++) {
				auto& v = x_even[i][l];
				x_even[l][i] = v > 1 ? 1 : v < -1 ? -1 : v;
			}
		}


		// auto-generated code for layer layer_9: Conv1d(4, 1, kernel_size=(1,), stride=(1,))
		const float w_layer_9[1][4][1] = {{{-0.3318099081516266},{-0.005131200421601534},{0.14994913339614868},{-0.05314330756664276}}};
		const float b_layer_9[1] = {-0.06243183836340904};

		// Fill with biases for layer_9
		for (int l = 511; l < L; l++) {
			for (int i = 0; i < 1; i++) {
				x_odd[l][i] = b_layer_9[i];
			}
		}

		// Apply main filter for layer_9
		// x_odd[:,511:] = sum(w[k]@x_even[:,511-(0-k)*0:L-(0-k)*0] for k in w.shape[0])
		for (int k = 0; k < 1; k++) {
			int offset = (0-k)*0;
			cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 1, L-511, 4, 1.0, &w_layer_9[k][0][0], 1, &x_even[511-offset][0], MAX_CH, 1.0, &x_odd[511][0], MAX_CH);
		}


		// Copy result back to y
		for (int l = 511; l < L; l++) {
			y[l] = x_odd[l][0];
		}
	}
};

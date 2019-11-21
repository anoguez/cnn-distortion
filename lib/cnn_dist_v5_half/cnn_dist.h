
extern "C" {
#include <cblas.h>
};

#include <cmath>

struct cnn_dist_v5 {
	const static int latency = 255;
	const static int MAX_L = MAX_BUFFER + latency;
	// About 1e-05*(MAX_BUFFER+255) MB of buffer
	float x_even[5][MAX_L];
	float x_odd [5][MAX_L];

	void operator()(float* x, float* y, int L) {

		// Ensure we don't segfault
		L = L > MAX_L ? MAX_L : L;

		for (int i = 0; i < L; i++) {
			x_odd[0][i] = x[i];
		}

		// auto-generated code for layer layer_0: Conv1d(1, 5, kernel_size=(2,), stride=(1,), dilation=(256,))
		const float w_layer_0[2][5][1] = {{{-1.5174957513809204},{-2.325819492340088},{0.682062029838562},{3.0602328777313232},{2.2338452339172363}},{{0.1990140974521637},{-0.2874305546283722},{-0.8522653579711914},{0.1270742565393448},{-0.028039010241627693}}};
		const float b_layer_0[5] = {0.3072108030319214,0.09693443775177002,-0.07003913819789886,0.04072875902056694,0.2817169427871704};

		// Fill with biases for layer_0
		for (int i = 0; i < 5; i++) {
			for (int l = 128; l < L; l++) {
				x_even[i][l] = b_layer_0[i];
			}
		}

		// Apply main filter for layer_0
		// x_even[:,128:] = sum(w[k]@x_odd[:,128-(1-k)*128:L-(1-k)*128] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*128;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 5, L-128, 1, 1.0, &w_layer_0[k][0][0], 1, &x_odd[0][128-offset], MAX_L, 1.0, &x_even[0][128], MAX_L);
		}


		// Leaky Rectified Linear Unit (ReLU)
		for (int i = 0; i < 5; i++) {
			for (int l = 128; l < L; l++) {
				x_even[i][l] = x_even[i][l] > 0 ? x_even[i][l] : 0.1f*x_even[i][l];
			}
		}


		// auto-generated code for layer layer_1: Conv1d(5, 5, kernel_size=(2,), stride=(1,), dilation=(128,))
		const float w_layer_1[2][5][5] = {{{-0.19892561435699463,-0.22364963591098785,0.15308843553066254,-1.5259698629379272,-0.6271213293075562},{0.24681775271892548,0.5190303325653076,-0.7724516987800598,-0.612443745136261,-0.43547186255455017},{-0.02849482372403145,-0.04568374156951904,-0.18985086679458618,0.039660241454839706,0.16655682027339935},{0.16792774200439453,0.25082358717918396,0.6153703331947327,-0.5331034660339355,-0.21986602246761322},{0.0014950450276955962,-0.14949174225330353,-0.14483101665973663,-0.07766616344451904,-0.006190143059939146}},{{-0.004699247889220715,0.2947359085083008,-0.47189024090766907,-0.23642241954803467,-0.39308851957321167},{-0.12352675944566727,-0.4581984579563141,0.032242126762866974,0.5638306140899658,0.26406151056289673},{0.6784940361976624,1.222366452217102,-0.3587695360183716,0.6928012371063232,-0.602412760257721},{0.3344762623310089,0.2066604644060135,-0.48735320568084717,0.08125197887420654,0.06777083873748779},{-0.7719361782073975,0.11023019999265671,-0.06960652768611908,1.3178445100784302,1.0962847471237183}}};
		const float b_layer_1[5] = {-0.20959937572479248,0.09559272229671478,-0.1537061333656311,0.15859851241111755,0.09787580370903015};

		// Fill with biases for layer_1
		for (int i = 0; i < 5; i++) {
			for (int l = 192; l < L; l++) {
				x_odd[i][l] = b_layer_1[i];
			}
		}

		// Apply main filter for layer_1
		// x_odd[:,192:] = sum(w[k]@x_even[:,192-(1-k)*64:L-(1-k)*64] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*64;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 5, L-192, 5, 1.0, &w_layer_1[k][0][0], 5, &x_even[0][192-offset], MAX_L, 1.0, &x_odd[0][192], MAX_L);
		}


		// Leaky Rectified Linear Unit (ReLU)
		for (int i = 0; i < 5; i++) {
			for (int l = 192; l < L; l++) {
				x_odd[i][l] = x_odd[i][l] > 0 ? x_odd[i][l] : 0.1f*x_odd[i][l];
			}
		}


		// auto-generated code for layer layer_2: Conv1d(5, 5, kernel_size=(2,), stride=(1,), dilation=(64,))
		const float w_layer_2[2][5][5] = {{{-0.12124399840831757,0.17178630828857422,-0.34027373790740967,-0.005361537914723158,0.31588879227638245},{0.15946266055107117,0.8084839582443237,-0.04669422283768654,0.26502102613449097,-0.06908760219812393},{0.2985689342021942,0.20710799098014832,0.42395809292793274,0.31149789690971375,-0.5428407192230225},{0.6539857983589172,-0.41406193375587463,0.43636563420295715,0.05003614351153374,-0.18345089256763458},{-0.7677098512649536,0.07651756703853607,-0.08195922523736954,0.09104406088590622,0.020778702571988106}},{{0.2489686906337738,0.32000935077667236,-0.07903619110584259,0.3254570960998535,0.014182846993207932},{-0.5320959687232971,0.09271420538425446,0.08582199364900589,-0.31547272205352783,-0.22130194306373596},{0.21698851883411407,0.37561771273612976,-0.5297544002532959,0.10747075080871582,0.5352643728256226},{0.24402567744255066,0.16197355091571808,-0.4100991487503052,0.206618532538414,0.30875465273857117},{-1.0359718799591064,-0.16670438647270203,-0.7162032127380371,-0.18538209795951843,1.0805394649505615}}};
		const float b_layer_2[5] = {0.013916893862187862,0.030047398060560226,0.17920562624931335,-0.19897182285785675,0.7827637195587158};

		// Fill with biases for layer_2
		for (int i = 0; i < 5; i++) {
			for (int l = 224; l < L; l++) {
				x_even[i][l] = b_layer_2[i];
			}
		}

		// Apply main filter for layer_2
		// x_even[:,224:] = sum(w[k]@x_odd[:,224-(1-k)*32:L-(1-k)*32] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*32;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 5, L-224, 5, 1.0, &w_layer_2[k][0][0], 5, &x_odd[0][224-offset], MAX_L, 1.0, &x_even[0][224], MAX_L);
		}


		// Leaky Rectified Linear Unit (ReLU)
		for (int i = 0; i < 5; i++) {
			for (int l = 224; l < L; l++) {
				x_even[i][l] = x_even[i][l] > 0 ? x_even[i][l] : 0.1f*x_even[i][l];
			}
		}


		// auto-generated code for layer layer_3: Conv1d(5, 5, kernel_size=(2,), stride=(1,), dilation=(32,))
		const float w_layer_3[2][5][5] = {{{-0.04583079367876053,-0.035909295082092285,0.5644345879554749,-0.6837491989135742,0.19320710003376007},{-0.2070784866809845,-1.0329796075820923,0.08258315920829773,-0.5528632998466492,0.20575451850891113},{-0.1954783946275711,0.025812281295657158,-0.12502548098564148,0.38863518834114075,-0.30914223194122314},{0.2696772813796997,-0.07000596076250076,0.11368154734373093,-0.28426095843315125,0.42936971783638},{-0.10156533122062683,0.09930739551782608,-0.5267819166183472,-0.19795957207679749,-0.6114705801010132}},{{-0.3190475404262543,-0.1316039115190506,0.42704275250434875,0.3125579357147217,-0.11377286165952682},{-0.11828731745481491,-0.1531129628419876,-0.05281520262360573,0.259006142616272,-0.06667345762252808},{0.09950502216815948,-0.09752967953681946,0.3468468189239502,0.6117663979530334,0.32947054505348206},{0.15259306132793427,0.13274994492530823,-0.22143493592739105,0.03010116145014763,0.12259731441736221},{0.42718732357025146,-0.039242662489414215,0.12125003337860107,0.23344849050045013,-0.29316335916519165}}};
		const float b_layer_3[5] = {-0.06094689667224884,0.21416865289211273,0.047136228531599045,0.04120580479502678,-0.07320204377174377};

		// Fill with biases for layer_3
		for (int i = 0; i < 5; i++) {
			for (int l = 240; l < L; l++) {
				x_odd[i][l] = b_layer_3[i];
			}
		}

		// Apply main filter for layer_3
		// x_odd[:,240:] = sum(w[k]@x_even[:,240-(1-k)*16:L-(1-k)*16] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*16;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 5, L-240, 5, 1.0, &w_layer_3[k][0][0], 5, &x_even[0][240-offset], MAX_L, 1.0, &x_odd[0][240], MAX_L);
		}


		// Leaky Rectified Linear Unit (ReLU)
		for (int i = 0; i < 5; i++) {
			for (int l = 240; l < L; l++) {
				x_odd[i][l] = x_odd[i][l] > 0 ? x_odd[i][l] : 0.1f*x_odd[i][l];
			}
		}


		// auto-generated code for layer layer_4: Conv1d(5, 5, kernel_size=(2,), stride=(1,), dilation=(16,))
		const float w_layer_4[2][5][5] = {{{-0.2940806448459625,0.4836355745792389,0.37226632237434387,-0.06805931031703949,-0.04209636524319649},{-0.19686435163021088,0.43524307012557983,0.21225537359714508,-0.2834843099117279,0.07825473695993423},{-0.06885895878076553,0.054083991795778275,0.864692211151123,-0.08815133571624756,0.06626828759908676},{0.068707175552845,0.011891214177012444,0.7487338781356812,0.06548486649990082,-0.29066377878189087},{0.34745699167251587,-0.24494056403636932,0.017049195244908333,-0.5217702388763428,0.30660855770111084}},{{0.10542672872543335,0.31703895330429077,0.015073345974087715,-0.07029072195291519,0.04000410810112953},{-0.2351115643978119,0.29675328731536865,-0.2668224573135376,-0.21406635642051697,0.44696664810180664},{0.23769748210906982,0.08207772672176361,-0.03495928645133972,-0.03331126272678375,-0.10448485612869263},{0.17783498764038086,-0.05088202282786369,0.034199174493551254,-0.29138851165771484,0.10206771641969681},{0.7375857830047607,0.31558099389076233,-0.18444602191448212,0.40354880690574646,-0.5537039637565613}}};
		const float b_layer_4[5] = {0.17681410908699036,-0.1770407110452652,-0.013323502615094185,-0.0033290155697613955,-0.10410778224468231};

		// Fill with biases for layer_4
		for (int i = 0; i < 5; i++) {
			for (int l = 248; l < L; l++) {
				x_even[i][l] = b_layer_4[i];
			}
		}

		// Apply main filter for layer_4
		// x_even[:,248:] = sum(w[k]@x_odd[:,248-(1-k)*8:L-(1-k)*8] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*8;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 5, L-248, 5, 1.0, &w_layer_4[k][0][0], 5, &x_odd[0][248-offset], MAX_L, 1.0, &x_even[0][248], MAX_L);
		}


		// Leaky Rectified Linear Unit (ReLU)
		for (int i = 0; i < 5; i++) {
			for (int l = 248; l < L; l++) {
				x_even[i][l] = x_even[i][l] > 0 ? x_even[i][l] : 0.1f*x_even[i][l];
			}
		}


		// auto-generated code for layer layer_5: Conv1d(5, 5, kernel_size=(2,), stride=(1,), dilation=(8,))
		const float w_layer_5[2][5][5] = {{{-0.14357510209083557,-0.21317559480667114,0.07668648660182953,-0.3958430290222168,-0.09996136277914047},{-0.2833363115787506,-0.19892065227031708,-0.3663109242916107,-0.32190272212028503,0.37206003069877625},{0.34798187017440796,0.26167258620262146,-0.22456242144107819,0.1913551390171051,-0.5427478551864624},{0.2960720658302307,-0.2232275903224945,0.4644266366958618,0.26491814851760864,0.132979616522789},{-0.17015960812568665,-0.3095438778400421,-0.36295709013938904,-0.3898848295211792,0.34994393587112427}},{{0.20769938826560974,-0.0018471889197826385,-0.021105598658323288,-0.3609832525253296,1.4750831127166748},{-0.10609835386276245,-0.23220153152942657,-0.09475217759609222,0.12944169342517853,0.004660537466406822},{0.21864748001098633,-0.028741318732500076,0.09496801346540451,-0.09247498214244843,0.28719526529312134},{-0.02317388355731964,-0.39981070160865784,0.16555757820606232,-0.12163369357585907,0.5388345122337341},{-0.07287322729825974,-0.31501367688179016,0.003297420684248209,0.23398494720458984,-0.3783104717731476}}};
		const float b_layer_5[5] = {0.10028498619794846,0.22275310754776,0.09666386991739273,-0.36521685123443604,0.20027369260787964};

		// Fill with biases for layer_5
		for (int i = 0; i < 5; i++) {
			for (int l = 252; l < L; l++) {
				x_odd[i][l] = b_layer_5[i];
			}
		}

		// Apply main filter for layer_5
		// x_odd[:,252:] = sum(w[k]@x_even[:,252-(1-k)*4:L-(1-k)*4] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*4;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 5, L-252, 5, 1.0, &w_layer_5[k][0][0], 5, &x_even[0][252-offset], MAX_L, 1.0, &x_odd[0][252], MAX_L);
		}


		// Leaky Rectified Linear Unit (ReLU)
		for (int i = 0; i < 5; i++) {
			for (int l = 252; l < L; l++) {
				x_odd[i][l] = x_odd[i][l] > 0 ? x_odd[i][l] : 0.1f*x_odd[i][l];
			}
		}


		// auto-generated code for layer layer_6: Conv1d(5, 5, kernel_size=(2,), stride=(1,), dilation=(4,))
		const float w_layer_6[2][5][5] = {{{-0.004523598589003086,-0.4826500415802002,0.355324387550354,0.1548987179994583,-0.24660305678844452},{0.1767541617155075,0.31181469559669495,-0.23932330310344696,-0.30415603518486023,0.31669336557388306},{0.41051432490348816,0.30771034955978394,-0.3923470377922058,-0.3317324221134186,-0.09549928456544876},{0.2246064990758896,-0.24411118030548096,-0.34018707275390625,0.23193107545375824,-1.0146021842956543},{-0.2505364418029785,-0.6447174549102783,0.34656545519828796,-0.45652303099632263,-0.4174075424671173}},{{0.3588404655456543,0.11355632543563843,-0.07814241200685501,-0.3949597477912903,-0.21004413068294525},{-0.5038482546806335,0.04015588387846947,0.03684178367257118,0.021662618964910507,0.40175697207450867},{0.341593861579895,0.34980982542037964,-0.27922195196151733,0.14775350689888,0.13110657036304474},{-0.11625397950410843,0.1760580837726593,-0.19011545181274414,-0.4031568169593811,0.4601048231124878},{0.03904559835791588,-0.27440083026885986,0.22382239997386932,0.02688344195485115,-0.8441632986068726}}};
		const float b_layer_6[5] = {0.13294120132923126,0.11949373781681061,0.0324048288166523,0.02216833084821701,0.1636633425951004};

		// Fill with biases for layer_6
		for (int i = 0; i < 5; i++) {
			for (int l = 254; l < L; l++) {
				x_even[i][l] = b_layer_6[i];
			}
		}

		// Apply main filter for layer_6
		// x_even[:,254:] = sum(w[k]@x_odd[:,254-(1-k)*2:L-(1-k)*2] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*2;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 5, L-254, 5, 1.0, &w_layer_6[k][0][0], 5, &x_odd[0][254-offset], MAX_L, 1.0, &x_even[0][254], MAX_L);
		}


		// Leaky Rectified Linear Unit (ReLU)
		for (int i = 0; i < 5; i++) {
			for (int l = 254; l < L; l++) {
				x_even[i][l] = x_even[i][l] > 0 ? x_even[i][l] : 0.1f*x_even[i][l];
			}
		}


		// auto-generated code for layer layer_7: Conv1d(5, 5, kernel_size=(2,), stride=(1,), dilation=(2,))
		const float w_layer_7[2][5][5] = {{{-0.5719835162162781,0.16107718646526337,0.23518423736095428,-0.9213617444038391,-0.1247120276093483},{-0.10062814503908157,-0.4490378499031067,0.020832600072026253,0.29478055238723755,0.3256111443042755},{0.1024293303489685,-0.13482031226158142,-0.3716776967048645,0.555266261100769,0.5762682557106018},{0.29008156061172485,-0.609166145324707,0.06529073417186737,0.49678805470466614,0.5472146272659302},{-0.33819639682769775,0.2968175411224365,0.3288441598415375,-0.247189000248909,-0.30094006657600403}},{{-0.2093302607536316,0.13707129657268524,0.16888484358787537,-0.03828969970345497,0.45370253920555115},{-0.549136757850647,-0.3718753159046173,-0.10680963099002838,0.1967153698205948,0.0272071473300457},{-0.1346319168806076,-0.22804203629493713,-0.3955250382423401,-0.03412001579999924,0.5166422724723816},{-0.04460592940449715,-0.5279816389083862,0.19148051738739014,-0.18886327743530273,0.0812426507472992},{-0.05564531683921814,0.3199043869972229,0.3543533384799957,0.6528040766716003,0.282629132270813}}};
		const float b_layer_7[5] = {0.11867167800664902,0.19288398325443268,-0.18542596697807312,0.26042529940605164,0.07247179001569748};

		// Fill with biases for layer_7
		for (int i = 0; i < 5; i++) {
			for (int l = 255; l < L; l++) {
				x_odd[i][l] = b_layer_7[i];
			}
		}

		// Apply main filter for layer_7
		// x_odd[:,255:] = sum(w[k]@x_even[:,255-(1-k)*1:L-(1-k)*1] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*1;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 5, L-255, 5, 1.0, &w_layer_7[k][0][0], 5, &x_even[0][255-offset], MAX_L, 1.0, &x_odd[0][255], MAX_L);
		}


		// Leaky Rectified Linear Unit (ReLU)
		for (int i = 0; i < 5; i++) {
			for (int l = 255; l < L; l++) {
				x_odd[i][l] = x_odd[i][l] > 0 ? x_odd[i][l] : 0.1f*x_odd[i][l];
			}
		}


		// auto-generated code for layer layer_8: Conv1d(5, 1, kernel_size=(1,), stride=(1,))
		const float w_layer_8[1][1][5] = {{{-0.26038748025894165,0.41697531938552856,0.4800845980644226,0.45467376708984375,-0.3020004332065582}}};
		const float b_layer_8[1] = {0.038802534341812134};

		// Fill with biases for layer_8
		for (int i = 0; i < 1; i++) {
			for (int l = 255; l < L; l++) {
				x_even[i][l] = b_layer_8[i];
			}
		}

		// Apply main filter for layer_8
		// x_even[:,255:] = sum(w[k]@x_odd[:,255-(0-k)*0:L-(0-k)*0] for k in w.shape[0])
		for (int k = 0; k < 1; k++) {
			int offset = (0-k)*0;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 1, L-255, 5, 1.0, &w_layer_8[k][0][0], 5, &x_odd[0][255-offset], MAX_L, 1.0, &x_even[0][255], MAX_L);
		}


		// Copy result back to y
		for (int l = 255; l < L; l++) {
			y[l] = x_even[0][l];
		}
	}
};

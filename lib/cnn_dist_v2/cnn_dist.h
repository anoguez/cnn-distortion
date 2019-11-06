
extern "C" {
#include <cblas.h>
};

struct cnn_dist_v2 {
	const static int latency = 510;
	const static int MAX_L = MAX_BUFFER + latency;
	// About 2e-05*(MAX_BUFFER+510) MB of buffer
	float x_even[10][MAX_L];
	float x_odd [10][MAX_L];

	void operator()(float* x, float* y, int L) {

		// Ensure we don't segfault
		L = L > MAX_L ? MAX_L : L;

		for (int i = 0; i < L; i++) {
			x_odd[0][i] = x[i];
		}

		// auto-generated code for layer layer_0: Conv1d(1, 10, kernel_size=(2,), stride=(1,), dilation=(256,))
		const float w_layer_0[2][10][1] = {{{2.1564700603485107},{-1.141950011253357},{0.7612673044204712},{0.9170317649841309},{0.0684414952993393},{-1.7378160953521729},{-0.23497380316257477},{1.2940490245819092},{-0.5211257934570312},{-1.4012607336044312}},{{-0.23246382176876068},{-0.13723953068256378},{0.1113286241889},{0.5343992710113525},{0.6276504397392273},{0.10553854703903198},{-0.6922324895858765},{-0.13105644285678864},{-0.1323838084936142},{0.20021535456180573}}};
		const float b_layer_0[10] = {0.04163498058915138,0.12633222341537476,0.17553777992725372,0.08310489356517792,-0.0223690178245306,0.05324971675872803,0.05398383364081383,0.09363868832588196,0.19554832577705383,0.45977863669395447};

		// Fill with biases for layer_0
		for (int i = 0; i < 10; i++) {
			for (int l = 256; l < L; l++) {
				x_even[i][l] = b_layer_0[i];
			}
		}

		// Apply main filter for layer_0
		// x_even[:,256:] = sum(w[k]@x_odd[:,256-(1-k)*256:L-(1-k)*256] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*256;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 10, L-256, 1, 1.0, &w_layer_0[k][0][0], 1, &x_odd[0][256-offset], MAX_L, 1.0, &x_even[0][256], MAX_L);
		}


		// Rectified Linear Unit (ReLU)
		for (int i = 0; i < 10; i++) {
			for (int l = 256; l < L; l++) {
				x_even[i][l] = x_even[i][l] > 0 ? x_even[i][l] : 0;
			}
		}


		// auto-generated code for layer layer_1: Conv1d(10, 10, kernel_size=(2,), stride=(1,), dilation=(128,))
		const float w_layer_1[2][10][10] = {{{-0.15143510699272156,-0.05739675089716911,-0.03137420490384102,-0.05989324301481247,0.09706392139196396,-0.1141907274723053,-0.07452528923749924,0.11876241117715836,-0.052436549216508865,-0.03442452847957611},{0.4011450409889221,-0.0802299752831459,0.3365528881549835,0.3487740457057953,0.13015159964561462,-0.2145276814699173,0.07452131807804108,0.28534069657325745,0.01853707991540432,0.02324099838733673},{-1.126820683479309,0.28560924530029297,-0.11315920203924179,-0.6078908443450928,-0.19561412930488586,0.33190229535102844,0.4847247302532196,-0.289834201335907,0.18016551434993744,0.12714266777038574},{0.26548442244529724,-0.2052897959947586,0.27612096071243286,0.22417005896568298,-0.2124258130788803,-0.13081321120262146,-0.2301492840051651,0.2601146996021271,-0.2078096568584442,-0.1901269555091858},{-0.49458229541778564,0.18232375383377075,0.07140935212373734,-0.5144731998443604,-0.39267104864120483,0.7501751184463501,0.27106937766075134,-0.2734513580799103,0.09058781713247299,0.18436837196350098},{0.05906681343913078,-0.0168923269957304,-0.02269507385790348,-0.2018118053674698,0.08261393010616302,0.18479248881340027,0.42796429991722107,-0.046475399285554886,-0.009309496730566025,0.09423869103193283},{-0.34947872161865234,-0.03313202038407326,0.039358094334602356,0.1841728836297989,0.11084786802530289,0.11715057492256165,-0.2771480679512024,-0.1178709864616394,0.1456511914730072,-0.05316787213087082},{0.10465431958436966,-0.19772087037563324,0.06188143417239189,-0.13650169968605042,0.02253410965204239,0.03817354887723923,0.16505107283592224,0.052240051329135895,0.016074560582637787,0.05128681659698486},{-0.4183766841888428,0.24833033978939056,-0.15118111670017242,-0.2050517499446869,-0.22762039303779602,0.370139479637146,0.03467552363872528,-0.3956031799316406,0.04604891315102577,0.2265060842037201},{0.4258253574371338,-0.014879665337502956,-0.00072655820986256,-0.004998743999749422,-0.06178003177046776,0.2540546655654907,0.06051233038306236,0.18234287202358246,-0.031952422112226486,-0.022862950339913368}},{{0.024601079523563385,-0.04944257438182831,-0.11319231241941452,-0.01837661676108837,-0.12107118219137192,-0.059891849756240845,-0.1277289092540741,-0.037446778267621994,0.14842644333839417,-0.04005516320466995},{-0.20726756751537323,0.2593896985054016,-0.06441148370504379,0.1451966017484665,-0.023811189457774162,0.1353536695241928,0.06582356244325638,-0.1155017763376236,0.2603522539138794,-0.01520861778408289},{0.08350512385368347,-0.20171773433685303,-0.08514634519815445,0.026311907917261124,0.026866795495152473,-1.3641451597213745,-0.014297141693532467,0.06907209008932114,-0.057470403611660004,0.0026022957172244787},{-0.3535557687282562,0.2703210115432739,-0.20590579509735107,-0.06153073161840439,0.35969868302345276,0.4621678590774536,0.02578149363398552,-0.29585739970207214,0.23629562556743622,0.25375306606292725},{-0.215037003159523,0.11914731562137604,-0.11787578463554382,0.10354012250900269,-0.5050089955329895,0.3382627069950104,0.07050459831953049,-0.0813240185379982,0.15121197700500488,0.33846816420555115},{0.09534034878015518,0.4058040976524353,-0.3931952714920044,-0.2923556864261627,0.054486654698848724,0.7306081056594849,0.08630234748125076,-0.12631218135356903,0.0717109963297844,0.2570916414260864},{-0.21767877042293549,0.4706645607948303,-0.23867090046405792,0.11005844920873642,-0.06676100194454193,0.7658894062042236,0.10290409624576569,-0.337807297706604,0.46486157178878784,0.25470051169395447},{-0.20752419531345367,0.13813833892345428,-0.11584171652793884,-0.06559018790721893,0.028942812234163284,0.3780500888824463,0.0601222962141037,-0.2889288663864136,0.10843977332115173,0.36681872606277466},{0.7168570756912231,-0.19034889340400696,0.041185688227415085,0.23416809737682343,0.11659986525774002,-0.20071005821228027,-0.28766581416130066,0.3451167047023773,-0.11853402853012085,-0.24043172597885132},{0.7612987756729126,-0.21373584866523743,0.13487465679645538,0.2713110148906708,0.041620686650276184,-0.06266263127326965,0.05682925507426262,0.4795055091381073,-0.282108873128891,-0.1351776123046875}}};
		const float b_layer_1[10] = {-0.046381182968616486,-0.06271535903215408,-0.15130864083766937,-0.02297157794237137,0.22913619875907898,0.16151706874370575,0.07327383011579514,0.18293923139572144,0.0871536135673523,0.05194452404975891};

		// Fill with biases for layer_1
		for (int i = 0; i < 10; i++) {
			for (int l = 384; l < L; l++) {
				x_odd[i][l] = b_layer_1[i];
			}
		}

		// Apply main filter for layer_1
		// x_odd[:,384:] = sum(w[k]@x_even[:,384-(1-k)*128:L-(1-k)*128] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*128;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 10, L-384, 10, 1.0, &w_layer_1[k][0][0], 10, &x_even[0][384-offset], MAX_L, 1.0, &x_odd[0][384], MAX_L);
		}


		// Rectified Linear Unit (ReLU)
		for (int i = 0; i < 10; i++) {
			for (int l = 384; l < L; l++) {
				x_odd[i][l] = x_odd[i][l] > 0 ? x_odd[i][l] : 0;
			}
		}


		// auto-generated code for layer layer_2: Conv1d(10, 10, kernel_size=(2,), stride=(1,), dilation=(64,))
		const float w_layer_2[2][10][10] = {{{0.1509796530008316,0.10673975944519043,-0.07316812127828598,0.28414177894592285,0.38487952947616577,0.11645152419805527,0.33982986211776733,0.45119014382362366,0.0017227756325155497,-0.22428104281425476},{0.13701047003269196,0.23901484906673431,0.460745632648468,-0.13616186380386353,-0.21570058166980743,-0.0791463628411293,0.13929978013038635,0.15917184948921204,-0.1621832698583603,0.2454518973827362},{0.050884559750556946,-0.13187693059444427,-0.028522878885269165,0.07746461033821106,0.11201870441436768,0.3345256447792053,0.24347060918807983,0.18642033636569977,-0.07720106095075607,-0.1256600022315979},{0.12043038010597229,-0.14763423800468445,0.26202115416526794,0.18667279183864594,-0.12409782409667969,0.05344986543059349,-0.06476513296365738,-0.14103125035762787,-0.04474538564682007,0.19278977811336517},{0.15610818564891815,-0.281509131193161,-0.28985723853111267,-0.057645510882139206,0.3120618164539337,-0.12684160470962524,0.21106886863708496,-0.10216306895017624,0.4855829179286957,-0.13981078565120697},{-0.04615309461951256,0.10277601331472397,0.1316961795091629,-0.06341292709112167,-0.14505590498447418,-0.34246373176574707,-0.3090110719203949,-0.27851754426956177,0.10448294878005981,0.19495920836925507},{-0.16980870068073273,0.17706818878650665,0.15214768052101135,0.1326543688774109,-0.38403433561325073,-0.16136044263839722,-0.012523864395916462,0.15680624544620514,-0.3337743878364563,0.05759378522634506},{-0.0800599604845047,0.15225538611412048,-0.009114902466535568,0.3345017731189728,0.13123105466365814,0.27017608284950256,0.46500158309936523,0.13842156529426575,-0.20933787524700165,-0.07866107672452927},{-0.052996497601270676,0.17145445942878723,-0.4715476632118225,0.2008475363254547,0.35987192392349243,0.12610910832881927,0.25686320662498474,0.02300241030752659,-0.026544423773884773,-0.10635525733232498},{0.11971374601125717,-0.1228698119521141,-0.9019669890403748,-0.395873099565506,0.11794646829366684,0.07077059149742126,-0.24419522285461426,-0.0981082022190094,0.39443454146385193,0.18601162731647491}},{{-0.05305689573287964,-0.29390281438827515,0.38374343514442444,-0.5225991010665894,-0.06078662723302841,-0.21894711256027222,-0.14249125123023987,-0.575070858001709,0.2772482931613922,0.30982986092567444},{0.15037217736244202,0.020455673336982727,0.06744154542684555,-0.11679669469594955,-0.2507473826408386,-0.017561744898557663,-0.052341707050800323,-0.31939107179641724,0.36476922035217285,0.36631911993026733},{-0.03916213661432266,-0.1427398920059204,-0.07559547573328018,-0.02873820811510086,0.31033554673194885,0.3032388389110565,0.18285539746284485,0.29503539204597473,0.22873352468013763,-0.17794720828533173},{-0.057240456342697144,0.04225052520632744,0.4062943160533905,0.3192683160305023,0.32598185539245605,0.2902633547782898,0.4724472165107727,0.6456578969955444,-0.16286154091358185,-0.13684454560279846},{-0.07126228511333466,0.24846048653125763,-0.5586672425270081,0.4245736598968506,-0.25690630078315735,-0.05942978337407112,0.002644760999828577,0.1343378871679306,0.09898511320352554,-0.10224823653697968},{-0.15401634573936462,0.25698819756507874,-0.2867685556411743,0.2846328318119049,-0.07037895917892456,0.30009374022483826,0.20236626267433167,0.24988500773906708,-0.16785700619220734,0.07267973572015762},{0.017624864354729652,-0.3344213366508484,0.1651313155889511,-0.32260143756866455,0.21151453256607056,0.01889527402818203,0.08300890773534775,-0.012772156856954098,0.12563639879226685,-0.06533578783273697},{0.01372208259999752,-0.007342184893786907,0.3363489508628845,0.1700747162103653,0.11393169313669205,-0.09797795116901398,-0.21676699817180634,0.204890176653862,-0.07119382917881012,-0.0294974185526371},{-0.16892334818840027,-0.011193260550498962,-0.0038044778630137444,-0.2581495940685272,0.09481161087751389,-0.2291385531425476,-0.2542760372161865,-0.11218811571598053,0.14190444350242615,0.11426915973424911},{0.09108605980873108,-0.10260437428951263,-0.4179084897041321,-0.26380860805511475,0.39609232544898987,0.16291415691375732,0.17604663968086243,-0.1384555846452713,0.29346033930778503,0.1625024378299713}}};
		const float b_layer_2[10] = {0.015724701806902885,0.2068752646446228,0.03249545395374298,0.1662103831768036,-0.010692480951547623,0.17525050044059753,0.026705892756581306,0.05590219423174858,0.0577208437025547,-0.1101439967751503};

		// Fill with biases for layer_2
		for (int i = 0; i < 10; i++) {
			for (int l = 448; l < L; l++) {
				x_even[i][l] = b_layer_2[i];
			}
		}

		// Apply main filter for layer_2
		// x_even[:,448:] = sum(w[k]@x_odd[:,448-(1-k)*64:L-(1-k)*64] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*64;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 10, L-448, 10, 1.0, &w_layer_2[k][0][0], 10, &x_odd[0][448-offset], MAX_L, 1.0, &x_even[0][448], MAX_L);
		}


		// Rectified Linear Unit (ReLU)
		for (int i = 0; i < 10; i++) {
			for (int l = 448; l < L; l++) {
				x_even[i][l] = x_even[i][l] > 0 ? x_even[i][l] : 0;
			}
		}


		// auto-generated code for layer layer_3: Conv1d(10, 10, kernel_size=(2,), stride=(1,), dilation=(32,))
		const float w_layer_3[2][10][10] = {{{0.19857275485992432,-0.15996691584587097,0.023051904514431953,-0.41878634691238403,-0.1498599648475647,-1.17876398563385,0.04063080996274948,0.14622090756893158,0.09814482182264328,0.007210212294012308},{-0.04466891288757324,-0.14101897180080414,0.2216201275587082,0.023508161306381226,0.4129646122455597,-0.16165994107723236,-0.13106368482112885,0.02909029647707939,0.014976328238844872,-0.06960566341876984},{0.02474919520318508,-0.2073040008544922,0.162985697388649,0.3043448030948639,-0.11036494374275208,-0.28508806228637695,-0.4651714861392975,0.23069047927856445,-0.09466392546892166,-0.10719408094882965},{-0.0784144178032875,0.37837979197502136,0.21183685958385468,0.1665043979883194,-0.5746870040893555,0.0026179132983088493,0.14325475692749023,0.20482327044010162,0.1073707640171051,-0.4928087294101715},{0.21776710450649261,0.12118769437074661,-0.05460018292069435,0.10791946202516556,0.25811025500297546,0.07133346050977707,0.20661547780036926,-0.1835063248872757,-0.048424992710351944,0.1280762404203415},{0.29837945103645325,0.6011877059936523,-0.14286373555660248,-0.38361912965774536,-0.23319034278392792,-0.5945470333099365,0.2965262830257416,-0.04019221290946007,0.1699453592300415,0.08157311379909515},{-0.30659475922584534,0.10388803482055664,0.12942638993263245,0.10024172812700272,-0.1467311978340149,0.2301766723394394,-0.05475425347685814,0.03386489674448967,0.13160662353038788,-0.5852163434028625},{-0.13603395223617554,-0.22519241273403168,0.30027249455451965,0.2329159826040268,0.2874830961227417,0.23231753706932068,0.09887029230594635,-0.012285866774618626,-0.4407024383544922,0.0953788012266159},{0.210774227976799,0.14405789971351624,-0.05512222275137901,-0.1663515418767929,0.5913489460945129,-0.16123268008232117,0.17098788917064667,-0.22878672182559967,0.11154628545045853,0.21503996849060059},{-0.45413532853126526,0.017985397949814796,0.34188002347946167,0.3028486967086792,0.11431500315666199,-0.13336443901062012,-0.1221880093216896,0.19837085902690887,-0.42777886986732483,0.07057967036962509}},{{0.08565551787614822,-0.16724500060081482,0.22946318984031677,0.08632133901119232,-0.10469390451908112,-0.34225112199783325,-0.03603512793779373,0.2844087481498718,0.10029245167970657,0.04307634383440018},{0.4209752082824707,0.37345948815345764,-0.02495243027806282,-0.14606516063213348,0.12996399402618408,-0.33981218934059143,-0.15234045684337616,0.015035383403301239,0.08785911649465561,0.05460897460579872},{0.40168172121047974,-0.34563198685646057,0.18118003010749817,0.05596039071679115,-0.07591835409402847,-0.25550803542137146,-0.10002382099628448,0.399752140045166,0.23205910623073578,-0.2794463634490967},{0.13350188732147217,0.12696875631809235,0.23400528728961945,0.22618083655834198,-0.3325500190258026,-0.01153632253408432,-0.0899987742304802,0.03177356347441673,-0.1653488129377365,-0.18697203695774078},{-0.289226233959198,-0.2844756543636322,0.09571065753698349,0.25368666648864746,0.19979748129844666,0.3780006170272827,0.11206051707267761,0.1907871961593628,-0.21982035040855408,0.03814578801393509},{0.035060375928878784,0.05499143898487091,0.3838818669319153,0.030408963561058044,-0.05614481121301651,-0.21634618937969208,0.2006252408027649,0.41342082619667053,0.1270671933889389,-0.11679708957672119},{0.24455367028713226,0.26932793855667114,0.11041297763586044,-0.020975109189748764,-0.49861475825309753,-0.05255576968193054,-0.09307566285133362,-0.18932640552520752,0.07534828782081604,-0.12853389978408813},{-0.32013359665870667,-0.36879006028175354,-0.14426210522651672,-0.2472342550754547,0.1245025098323822,-0.7486147880554199,0.4046880304813385,-0.04571425914764404,0.29387953877449036,-0.07317138463258743},{-0.3964095413684845,-0.31067296862602234,0.24977289140224457,0.13724170625209808,0.07272911071777344,-0.2556087374687195,0.1541401594877243,0.0009247836424037814,0.08763612806797028,-0.09903629869222641},{-0.2522977292537689,0.3712025582790375,-0.18539606034755707,0.14101780951023102,0.1772448718547821,0.1132158637046814,0.17124392092227936,-0.266071617603302,-0.2303154319524765,-0.044891323894262314}}};
		const float b_layer_3[10] = {-0.20346760749816895,0.04947104677557945,0.1625872701406479,0.21892410516738892,0.030939636752009392,-0.04834277927875519,0.06647516041994095,-0.05785556882619858,0.12987291812896729,0.0534493662416935};

		// Fill with biases for layer_3
		for (int i = 0; i < 10; i++) {
			for (int l = 480; l < L; l++) {
				x_odd[i][l] = b_layer_3[i];
			}
		}

		// Apply main filter for layer_3
		// x_odd[:,480:] = sum(w[k]@x_even[:,480-(1-k)*32:L-(1-k)*32] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*32;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 10, L-480, 10, 1.0, &w_layer_3[k][0][0], 10, &x_even[0][480-offset], MAX_L, 1.0, &x_odd[0][480], MAX_L);
		}


		// Rectified Linear Unit (ReLU)
		for (int i = 0; i < 10; i++) {
			for (int l = 480; l < L; l++) {
				x_odd[i][l] = x_odd[i][l] > 0 ? x_odd[i][l] : 0;
			}
		}


		// auto-generated code for layer layer_4: Conv1d(10, 10, kernel_size=(2,), stride=(1,), dilation=(16,))
		const float w_layer_4[2][10][10] = {{{0.246523916721344,0.20734243094921112,0.08624467998743057,0.18066030740737915,-0.3221834599971771,-0.27067896723747253,0.14956335723400116,-0.2755453884601593,-0.5854421854019165,0.11218806356191635},{0.18792101740837097,-0.061353545635938644,-0.01371291559189558,0.2245267629623413,-0.13457630574703217,0.28517797589302063,0.12871204316616058,-0.36219874024391174,-0.4474935829639435,-0.2179928570985794},{-0.09136812388896942,-0.12821145355701447,-0.1431042104959488,-0.04260639101266861,0.03732609003782272,0.04413892701268196,0.08155331015586853,0.13489007949829102,-0.13412262499332428,-0.008077358826994896},{0.17472940683364868,0.3160085380077362,-0.11739017814397812,0.004597673192620277,-0.3510662913322449,0.16809327900409698,-0.08420618623495102,0.18577569723129272,-0.0675819143652916,0.022608373314142227},{0.12639418244361877,-0.16936412453651428,-0.10266060382127762,0.05772949382662773,-0.20125830173492432,-0.0765671357512474,-0.022440815344452858,0.11812160909175873,-0.18269705772399902,-0.06431513279676437},{-0.04943140223622322,-0.05414943769574165,-0.05011363700032234,-0.02908134274184704,-0.034362852573394775,0.05294027179479599,-0.033430639654397964,-0.011428655125200748,-0.08338996022939682,-0.001114203012548387},{0.06654181331396103,0.31919193267822266,-0.01340004988014698,-1.7854414181783795e-05,-0.44465371966362,-0.14171312749385834,0.2910183370113373,0.6002265214920044,-0.49929752945899963,-0.032935671508312225},{-0.15620402991771698,0.058604612946510315,-0.05720322206616402,0.26110604405403137,-0.3030919134616852,-0.15435966849327087,0.40859776735305786,0.6699287295341492,-0.3114525079727173,0.06465909630060196},{0.022975746542215347,-0.09561193734407425,-0.3610028922557831,0.04566430673003197,-0.06748106330633163,0.40003854036331177,-0.07618734240531921,-0.12795928120613098,-0.21639706194400787,-0.04382920637726784},{0.029115041717886925,0.05818285048007965,-0.07238422334194183,-0.10404584556818008,-0.015475612133741379,-0.12224147468805313,-0.13675285875797272,-0.06316392868757248,0.10432923585176468,0.021020615473389626}},{{0.5672999024391174,0.07218006253242493,-0.21896882355213165,0.017061378806829453,0.038496233522892,0.035301364958286285,-0.3093370199203491,-0.24978943169116974,0.20927579700946808,0.1416553556919098},{0.4099321961402893,-0.23982974886894226,0.01628791354596615,-0.03496084734797478,-0.06668273359537125,0.0991264283657074,0.07891449332237244,0.0012211240828037262,0.16413645446300507,-0.5029153227806091},{-0.17936424911022186,0.10992708802223206,-0.15658485889434814,-0.17316487431526184,-0.10240404307842255,-0.02279776707291603,0.10368214547634125,-0.046701062470674515,0.07052921503782272,-0.0749315395951271},{-0.16637100279331207,0.036307040601968765,0.22517478466033936,0.08928953111171722,-0.07067301869392395,0.3621741831302643,0.1805633008480072,0.3528556525707245,0.23320302367210388,-0.04680440202355385},{-0.0336054265499115,0.08597201853990555,-0.10078706592321396,-0.09628123044967651,0.034665871411561966,0.12704190611839294,0.08477163314819336,-0.11228390038013458,-0.1535305231809616,0.07554261386394501},{-0.023792585358023643,0.0058440156280994415,0.04775754362344742,-0.10393201559782028,-0.20114675164222717,0.05943960323929787,-0.04646977409720421,-0.16536593437194824,-0.13952188193798065,-0.03402283415198326},{0.19398169219493866,0.015287196263670921,0.2836894989013672,0.20992480218410492,-0.04510034620761871,-0.009454619139432907,0.12629003822803497,0.0613199919462204,0.022533195093274117,0.13361522555351257},{-0.18442018330097198,0.06966616213321686,0.06639942526817322,0.23275543749332428,0.10579192638397217,-0.38898223638534546,0.2547838091850281,-0.27718889713287354,-0.10375697910785675,-0.011726167984306812},{0.2068759799003601,0.19653457403182983,0.20718781650066376,0.43290504813194275,-0.064423106610775,-0.7616453766822815,0.03671267256140709,1.1068443059921265,0.1876739263534546,0.6070020794868469},{-0.16039955615997314,0.06525364518165588,-0.03926195576786995,0.08666703850030899,-0.03155536949634552,-0.10912684351205826,-0.16533587872982025,-0.16167183220386505,-0.1404881328344345,-0.10706978291273117}}};
		const float b_layer_4[10] = {0.08219893276691437,-0.15280406177043915,-0.11327491700649261,0.03044934943318367,-0.18238753080368042,-0.14678484201431274,0.12136469036340714,0.18559055030345917,0.16359394788742065,-0.1378554105758667};

		// Fill with biases for layer_4
		for (int i = 0; i < 10; i++) {
			for (int l = 496; l < L; l++) {
				x_even[i][l] = b_layer_4[i];
			}
		}

		// Apply main filter for layer_4
		// x_even[:,496:] = sum(w[k]@x_odd[:,496-(1-k)*16:L-(1-k)*16] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*16;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 10, L-496, 10, 1.0, &w_layer_4[k][0][0], 10, &x_odd[0][496-offset], MAX_L, 1.0, &x_even[0][496], MAX_L);
		}


		// Rectified Linear Unit (ReLU)
		for (int i = 0; i < 10; i++) {
			for (int l = 496; l < L; l++) {
				x_even[i][l] = x_even[i][l] > 0 ? x_even[i][l] : 0;
			}
		}


		// auto-generated code for layer layer_5: Conv1d(10, 10, kernel_size=(2,), stride=(1,), dilation=(8,))
		const float w_layer_5[2][10][10] = {{{0.18247416615486145,0.12659478187561035,-0.07686168700456619,-0.08562140166759491,-0.1278218775987625,0.1820903718471527,-0.19890588521957397,0.01729763299226761,-0.16039709746837616,0.1535061001777649},{-0.09917803853750229,-0.13398659229278564,0.04438101127743721,0.3446435034275055,0.023729640990495682,-0.13641801476478577,0.20850837230682373,-0.042948417365550995,-0.15706199407577515,0.1341697871685028},{0.28701114654541016,0.08781896531581879,-0.06665939092636108,0.2490476816892624,0.15915252268314362,-0.12227968126535416,0.23561550676822662,0.12921710312366486,0.17862167954444885,-0.010578411631286144},{0.18527257442474365,-0.07734814286231995,0.13052381575107574,0.13358864188194275,-0.09308867156505585,0.010057172738015652,-0.09000663459300995,-0.032217174768447876,-0.12667874991893768,-0.04983963072299957},{-0.35132917761802673,0.051895588636398315,-0.03908639773726463,0.2106306552886963,-0.00018500059377402067,0.0773797333240509,-0.6926656365394592,-0.05279006063938141,-0.3420238792896271,-0.0994025468826294},{0.01592189632356167,-0.03440288081765175,-0.005593855399638414,0.03454108536243439,0.10077172517776489,-0.16330745816230774,-0.07562192529439926,-0.009483578614890575,-0.012707059271633625,0.07984007149934769},{-0.04669700562953949,0.21095164120197296,0.1362685263156891,-0.18397191166877747,-0.13270054757595062,-0.05021457374095917,-0.08323557674884796,0.22564473748207092,0.3246512711048126,0.04694584384560585},{-0.1451457440853119,-0.6068864464759827,-0.06330300867557526,-0.08884494006633759,-0.03347684442996979,0.1487446427345276,-0.23303458094596863,0.035168908536434174,0.33654341101646423,0.08482246845960617},{0.2295183539390564,0.20615564286708832,0.1327560991048813,0.13452789187431335,-0.05460110679268837,-0.021796144545078278,0.33211541175842285,0.39925166964530945,0.13975445926189423,0.11386360973119736},{-0.35319873690605164,0.15209634602069855,-0.13870713114738464,0.22458072006702423,0.007589961402118206,-0.10326992720365524,-0.1332014948129654,-0.2243652641773224,-0.22262661159038544,0.0875612273812294}},{{0.024805262684822083,-0.18665379285812378,0.05237741395831108,0.07918599992990494,-0.13449862599372864,-0.018672769889235497,0.09460118412971497,0.050520095974206924,0.4054153263568878,0.1017724871635437},{-0.05246613547205925,-0.1843978762626648,0.07789501547813416,0.3493778705596924,0.12307734787464142,0.12760864198207855,0.005744637455791235,-0.03512873500585556,-0.183505579829216,-0.02581142634153366},{0.295350581407547,-0.27880561351776123,-0.11413832008838654,0.1038583442568779,0.030403580516576767,-0.14948739111423492,-0.029957637190818787,-0.31904223561286926,-0.22631701827049255,0.1387677788734436},{0.3116207718849182,-0.3000276982784271,0.17358024418354034,0.13113631308078766,0.06695178896188736,-0.06607465445995331,0.15806524455547333,0.008417977951467037,0.27191266417503357,0.061818815767765045},{-0.4390859603881836,0.08773884922266006,0.13980059325695038,-0.1810532957315445,0.06265300512313843,-0.10025141388177872,0.19083872437477112,0.034498170018196106,-0.13695311546325684,-0.12825241684913635},{-0.16061246395111084,0.08832579851150513,-0.07151001691818237,-0.15055188536643982,0.01579434424638748,-0.027101917192339897,0.11124997586011887,-0.021432049572467804,-0.1095169261097908,0.06683755666017532},{0.3217398524284363,-0.8266198039054871,-0.16300351917743683,0.12174434959888458,-0.17377343773841858,0.0765056386590004,-0.09233934432268143,-0.08648993074893951,-0.6155494451522827,-0.00624109199270606},{0.2969822883605957,-0.7006431221961975,-0.10662595182657242,0.024870729073882103,0.023094655945897102,0.13352857530117035,0.09290461987257004,0.07095594704151154,0.1634601503610611,-0.1070970669388771},{0.10198388993740082,0.14537088572978973,0.1330915093421936,0.05202433839440346,-0.12608212232589722,-0.11288421601057053,-0.024842815473675728,0.23360830545425415,-0.009010395035147667,-0.0815519317984581},{-0.747275710105896,-0.5029939413070679,-0.012837044894695282,0.05112658813595772,-0.07116323709487915,0.004757673013955355,-0.0016203151317313313,0.23493531346321106,0.09481437504291534,-0.10563519597053528}}};
		const float b_layer_5[10] = {0.040037237107753754,0.26124390959739685,-0.13330064713954926,-0.11079208552837372,0.18455855548381805,-0.1863507181406021,0.08201106637716293,-0.04802972823381424,-0.06440752744674683,0.13567803800106049};

		// Fill with biases for layer_5
		for (int i = 0; i < 10; i++) {
			for (int l = 504; l < L; l++) {
				x_odd[i][l] = b_layer_5[i];
			}
		}

		// Apply main filter for layer_5
		// x_odd[:,504:] = sum(w[k]@x_even[:,504-(1-k)*8:L-(1-k)*8] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*8;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 10, L-504, 10, 1.0, &w_layer_5[k][0][0], 10, &x_even[0][504-offset], MAX_L, 1.0, &x_odd[0][504], MAX_L);
		}


		// Rectified Linear Unit (ReLU)
		for (int i = 0; i < 10; i++) {
			for (int l = 504; l < L; l++) {
				x_odd[i][l] = x_odd[i][l] > 0 ? x_odd[i][l] : 0;
			}
		}


		// auto-generated code for layer layer_6: Conv1d(10, 10, kernel_size=(2,), stride=(1,), dilation=(4,))
		const float w_layer_6[2][10][10] = {{{-0.3959819972515106,0.18073388934135437,0.4012513756752014,-0.025194887071847916,-0.6492490172386169,0.13393226265907288,-0.0885452926158905,0.03663402795791626,0.27895545959472656,0.03373793885111809},{0.11513668298721313,-0.09415300190448761,-0.023759450763463974,-0.08739711344242096,0.24875132739543915,-0.07524954527616501,-0.442396879196167,0.09087007492780685,-0.13588912785053253,0.3641704022884369},{-0.19372299313545227,-0.12918782234191895,0.2866092920303345,0.0917624682188034,0.1121557205915451,-0.11967486143112183,0.6271504163742065,0.37156158685684204,-0.1617448627948761,-0.272331565618515},{-0.17198403179645538,0.03134952485561371,0.18218359351158142,0.014107858762145042,-0.23249033093452454,-0.13424646854400635,-0.040492791682481766,0.03368384763598442,0.4120701551437378,-0.11374307423830032},{0.08130363374948502,-0.08906705677509308,-0.04133756086230278,-0.06386294215917587,0.1497730314731598,-0.121012382209301,-0.0845123678445816,-0.1284945160150528,-0.12791714072227478,-0.13423465192317963},{0.016912147402763367,0.21225203573703766,0.1722109615802765,-0.19833984971046448,-0.018991803750395775,-0.01044943556189537,0.41943445801734924,0.20270267128944397,0.12408733367919922,0.009028100408613682},{0.04068871960043907,-0.2657183110713959,-0.404808908700943,-0.1244383156299591,-0.08993375301361084,0.17587636411190033,-0.16292208433151245,0.5727145075798035,0.27104651927948,0.598154604434967},{0.13318723440170288,-0.07390199601650238,-0.011533880606293678,0.1143902838230133,-0.34437403082847595,-0.14129623770713806,0.18628467619419098,0.30945032835006714,0.32571080327033997,0.19267258048057556},{-0.09958609193563461,-0.10135049372911453,-0.1423514485359192,0.08848138898611069,0.13169240951538086,-0.17337943613529205,-0.07941780239343643,0.057410843670368195,-0.15293383598327637,0.13528715074062347},{0.1418161392211914,0.3552604019641876,-0.12662148475646973,0.17966704070568085,0.5547126531600952,-0.1066453605890274,-0.40178340673446655,-0.08563054352998734,-0.2721664309501648,0.35096102952957153}},{{-0.5288881063461304,0.3526574373245239,0.1769716888666153,-0.22429007291793823,0.1763055920600891,-0.10348158329725266,0.4462539553642273,-0.1653733253479004,0.11757048964500427,-0.1167534813284874},{0.23408278822898865,0.0364944189786911,0.43728384375572205,0.3168310225009918,-0.20344232022762299,0.03690513223409653,-0.38833901286125183,0.18217021226882935,0.012330827303230762,0.33114200830459595},{-0.15407061576843262,-0.028631767258048058,0.37254074215888977,0.2131827175617218,0.3348575532436371,0.010168452747166157,-0.08954861760139465,0.0925169587135315,0.09550407528877258,-0.09518145769834518},{-0.40107816457748413,-0.019216522574424744,-0.09278879314661026,-0.12197844684123993,0.22863662242889404,0.020032228901982307,-0.07646042108535767,-0.1417897641658783,-0.027301907539367676,0.003902750089764595},{-0.13077771663665771,0.06729990243911743,0.031285226345062256,0.011445225216448307,-0.16353696584701538,-0.1599540114402771,0.0558321550488472,0.05208194628357887,0.03337496519088745,-0.08955041319131851},{0.1861160844564438,0.09885197132825851,0.17736190557479858,0.016080209985375404,0.10792338103055954,0.11956272274255753,-0.08123026043176651,0.21145017445087433,-0.2758166790008545,0.005723508540540934},{-0.12209529429674149,-0.16407114267349243,-0.33527863025665283,-0.2129654437303543,0.5473540425300598,-0.05600323528051376,1.1745474338531494,0.0550500825047493,0.10737384110689163,0.2919140160083771},{0.1343318521976471,-0.10894633829593658,-0.2314714640378952,-0.22404420375823975,0.16462105512619019,-0.14185038208961487,0.41221222281455994,0.21145178377628326,0.20038412511348724,0.21021585166454315},{0.03498028218746185,-0.12903966009616852,-0.07717110216617584,-0.0014439062215387821,0.15086963772773743,0.06194525212049484,-0.1379941999912262,0.0496167428791523,-0.1603323221206665,0.0746351033449173},{0.1592894196510315,0.19719228148460388,-0.02030220814049244,0.21964384615421295,0.5391209125518799,0.050783757120370865,-0.18465162813663483,0.00485204067081213,-0.1702345758676529,0.15074317157268524}}};
		const float b_layer_6[10] = {-0.07551296800374985,-0.16224302351474762,-0.023638568818569183,0.025636011734604836,-0.04287593811750412,-0.1855623871088028,0.24264468252658844,0.052728231996297836,-0.1522674560546875,0.22462595999240875};

		// Fill with biases for layer_6
		for (int i = 0; i < 10; i++) {
			for (int l = 508; l < L; l++) {
				x_even[i][l] = b_layer_6[i];
			}
		}

		// Apply main filter for layer_6
		// x_even[:,508:] = sum(w[k]@x_odd[:,508-(1-k)*4:L-(1-k)*4] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*4;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 10, L-508, 10, 1.0, &w_layer_6[k][0][0], 10, &x_odd[0][508-offset], MAX_L, 1.0, &x_even[0][508], MAX_L);
		}


		// Rectified Linear Unit (ReLU)
		for (int i = 0; i < 10; i++) {
			for (int l = 508; l < L; l++) {
				x_even[i][l] = x_even[i][l] > 0 ? x_even[i][l] : 0;
			}
		}


		// auto-generated code for layer layer_7: Conv1d(10, 10, kernel_size=(2,), stride=(1,), dilation=(2,))
		const float w_layer_7[2][10][10] = {{{0.003615180728957057,0.08915198594331741,-0.0893973708152771,-0.022926777601242065,-0.009288224391639233,0.09742143750190735,0.15436524152755737,-0.17473949491977692,0.1253068447113037,-0.11294428259134293},{0.03611253201961517,-0.022845081984996796,-0.06314707547426224,0.30829063057899475,0.12545189261436462,0.19468221068382263,0.22038167715072632,0.3425907492637634,-0.12189910560846329,-0.2771260738372803},{-0.3899303376674652,0.11735812574625015,0.40713876485824585,-0.2635971009731293,-0.02317502163350582,0.3098643124103546,0.12118788063526154,0.2022371143102646,-0.002515333704650402,0.1409491002559662},{-0.14024601876735687,-0.10227763652801514,-0.023994870483875275,-0.000585356610827148,0.15878121554851532,-0.09903134405612946,0.1145586147904396,-0.19640560448169708,0.17105506360530853,-0.12623420357704163},{-0.014808787032961845,-0.11046196520328522,0.038544535636901855,-0.09342470020055771,-0.025852911174297333,0.10904356837272644,-0.14109911024570465,-0.061107050627470016,0.06170622259378433,-0.13248367607593536},{-0.3836527168750763,-0.05386122316122055,0.4177844226360321,-0.26813802123069763,-0.13331812620162964,-0.06583382189273834,0.2397126704454422,-0.16288374364376068,-0.001568303443491459,0.26699796319007874},{-0.08575834333896637,-0.2095039337873459,-0.03424563258886337,-0.10824761539697647,0.05311892554163933,-0.24294370412826538,-0.06961195915937424,-0.07637897878885269,-0.09814445674419403,0.3541671931743622},{-0.13716983795166016,-0.026925787329673767,-0.06093667075037956,-0.14409139752388,0.13583484292030334,0.16943208873271942,-0.05992048606276512,0.046274762600660324,-0.0964033305644989,-0.15621772408485413},{-0.6296806335449219,-0.3404588997364044,0.3236117660999298,-0.3801087737083435,-0.0158135574311018,-0.05019695684313774,-0.05903957784175873,0.12402299791574478,-0.001560270437039435,0.28535881638526917},{0.1954813152551651,-0.2928328216075897,-0.25394192337989807,0.17615863680839539,-0.03536521643400192,-0.11646843701601028,0.050153594464063644,-0.07772091776132584,0.12903660535812378,-0.2224225401878357}},{{-0.10953568667173386,0.040020428597927094,0.05447981134057045,-0.17240560054779053,-0.06323783099651337,-0.16703297197818756,-0.12242542952299118,-0.14383256435394287,-0.09479187428951263,-0.1155935525894165},{0.15783894062042236,-0.042255647480487823,-0.2576524615287781,0.06309706717729568,-0.023492086678743362,-0.18245410919189453,0.3456938564777374,0.3400428295135498,-0.13856111466884613,0.00783384870737791},{0.08250802010297775,0.29227542877197266,0.07656422257423401,0.28255710005760193,-0.05948472395539284,-0.08734556287527084,-0.048988476395606995,0.05367813631892204,0.03667207434773445,-0.317477822303772},{0.06567981094121933,0.0404178686439991,-0.09475777298212051,0.04984534531831741,0.007389441132545471,0.09385503828525543,0.0551898218691349,-0.08186675608158112,0.07573394477367401,-0.17019225656986237},{0.11390312761068344,-0.1612360179424286,0.03688092529773712,-0.15939292311668396,-0.12436585128307343,-0.16073879599571228,-0.17363004386425018,0.008870827965438366,-0.043522752821445465,-0.15054453909397125},{-0.24965670704841614,-0.14674721658229828,0.013430925086140633,-0.11174725741147995,-0.1677805781364441,0.10593579709529877,-0.013476516120135784,-0.05036906525492668,0.05100378766655922,0.10168354958295822},{-0.09435174614191055,0.034099943935871124,0.23027583956718445,0.03258071094751358,-0.17858374118804932,0.03695392981171608,0.0475439727306366,-0.149430513381958,-0.0035334208514541388,0.2143692821264267},{0.07596603780984879,-0.08155784755945206,-0.08697793632745743,0.14369264245033264,0.1308119148015976,-0.16214480996131897,-0.03574815019965172,0.03150852024555206,0.11597947776317596,0.11334570497274399},{-0.629348874092102,-0.22669717669487,0.16662098467350006,-0.09787958860397339,0.1471165269613266,-0.13073329627513885,0.2525671124458313,0.12684936821460724,0.17456892132759094,0.17268382012844086},{0.22670969367027283,0.07358086854219437,-0.19039739668369293,-0.0094091035425663,-0.026361631229519844,0.1513354778289795,-0.06343133002519608,0.11454223096370697,-0.0348043330013752,-0.075586698949337}}};
		const float b_layer_7[10] = {-0.11021142452955246,0.012184083461761475,-0.19062703847885132,-0.038558974862098694,-0.15526826679706573,0.276904433965683,0.2020982950925827,-0.11808208376169205,0.163416787981987,-0.2431449592113495};

		// Fill with biases for layer_7
		for (int i = 0; i < 10; i++) {
			for (int l = 510; l < L; l++) {
				x_odd[i][l] = b_layer_7[i];
			}
		}

		// Apply main filter for layer_7
		// x_odd[:,510:] = sum(w[k]@x_even[:,510-(1-k)*2:L-(1-k)*2] for k in w.shape[0])
		for (int k = 0; k < 2; k++) {
			int offset = (1-k)*2;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 10, L-510, 10, 1.0, &w_layer_7[k][0][0], 10, &x_even[0][510-offset], MAX_L, 1.0, &x_odd[0][510], MAX_L);
		}


		// Rectified Linear Unit (ReLU)
		for (int i = 0; i < 10; i++) {
			for (int l = 510; l < L; l++) {
				x_odd[i][l] = x_odd[i][l] > 0 ? x_odd[i][l] : 0;
			}
		}


		// auto-generated code for layer layer_8: Conv1d(10, 1, kernel_size=(1,), stride=(1,))
		const float w_layer_8[1][1][10] = {{{0.14251740276813507,0.32071125507354736,-0.15203353762626648,0.12215545028448105,0.025256332010030746,-0.3905584514141083,-0.17862066626548767,-0.11886033415794373,-0.4461778700351715,-0.20966316759586334}}};
		const float b_layer_8[1] = {0.09131549298763275};

		// Fill with biases for layer_8
		for (int i = 0; i < 1; i++) {
			for (int l = 510; l < L; l++) {
				x_even[i][l] = b_layer_8[i];
			}
		}

		// Apply main filter for layer_8
		// x_even[:,510:] = sum(w[k]@x_odd[:,510-(0-k)*1:L-(0-k)*1] for k in w.shape[0])
		for (int k = 0; k < 1; k++) {
			int offset = (0-k)*1;
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 1, L-510, 10, 1.0, &w_layer_8[k][0][0], 10, &x_odd[0][510-offset], MAX_L, 1.0, &x_even[0][510], MAX_L);
		}


		// Copy result back to y
		for (int l = 510; l < L; l++) {
			y[l] = x_even[0][l];
		}
	}
};

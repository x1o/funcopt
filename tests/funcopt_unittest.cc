// FIXME: see https://forum.qt.io/topic/74176/using-google-test-with-qtcreator-and-autotest-plugin
#include <sstream>
#include <iostream>
#include <exception>
#include <cmath>	// ctd::sin

#include "gtest/gtest.h"

#include "Point.h"
//#include "Domain.h"
//#include "scalar_fields.h"
//#include "Function.h"
//#include "DirectionFunction.h"
//#include "ConjugateGradient.h"
//#include "StopIterCriteria.h"
//#include "MaxIterCriterion.h"
//#include "ValDiffCriterion.h"
//#include "OptMethods.h"

TEST(PointOps, ScalarMagnification) {
  Point p = {-4, 3, 1};
  double r = 3.5;
  Point result = {-14, 10.5, 3.5};
  EXPECT_EQ(p * r, result);
  EXPECT_EQ(r * p, result);
}

TEST(PointOps, UnitaryMinus) {
  Point p = {-4, 3, 0};
  Point result = {4, -3, 0};
  EXPECT_EQ(-p, result);
}

TEST(PointOps, Sum) {
  Point p = {-4, 3, 1};
  Point q = {1, 0, 4.5};
  Point r = {1, 0};
  Point result = {-3, 3, 5.5};
  EXPECT_EQ(p + q, result);
  EXPECT_THROW(q + r, std::invalid_argument);
}

TEST(PointOps, Difference) {
  Point p = {-4, 3, 1};
  Point q = {1, 0, 4.5};
  Point result = {-5, 3, -3.5};
  EXPECT_EQ(p - q, result);
}

TEST(PointOps, ElementWiseDivision) {
  Point p = {-4, 3, 5};
  Point q = {1, 1.5, 2};
  Point result = {-4, 2, 2.5};
  EXPECT_EQ(p / q, result);
}

TEST(PointOps, DotProduct) {
  Point p = {-4, 3, 1};
  Point q = {2, 9, 0};
  EXPECT_EQ(p * q, 19);
}

TEST(PointMethods, IsZero) {
  Point p1 = {-4.4, 3, 1};
  Point p2 = {0, 0, 0};
  Point p3 = {0.00000000003, 0, 0.0000000004};
  Point p4 = {0.00000000003, 0, 0.004};
  EXPECT_FALSE(p1.IsZero());
  EXPECT_TRUE(p2.IsZero());
  EXPECT_TRUE(p3.IsZero());
  EXPECT_FALSE(p4.IsZero());
  EXPECT_TRUE(p4.IsZero(10e-2));
}

TEST(PointOps, Repr) {
  Point p1 = {-4, 3.5, 1};
  std::stringstream ss;
  ss << p1;
  EXPECT_EQ(ss.str(), "[-4, 3.5, 1]");
  Point p2(0);
  ss.str("");
  ss << p2;
  EXPECT_EQ(ss.str(), "[]");
}

TEST(PointMethods, L2Norm) {
  Point p = {-4, 3, 1};
  EXPECT_NEAR(p.L2Norm(), 5.09901951359278, 10e-6);
}

//TEST(DomainOps, Repr) {
//	Domain d = {{-5, 5}, {0, 3}};
//	std::stringstream ss;
//	ss << d;
//	EXPECT_EQ(ss.str(), "[[-5, 5], [0, 3]]");
//	ss.str("");
//	Domain e(d);
//	ss << e;
//	EXPECT_EQ(ss.str(), "[[-5, 5], [0, 3]]");
//}

//TEST(Domain, Constructors) {
//	Domain d(Domain {{-5, 5}, {0, 3}});
//	std::stringstream ss;
//	ss << d;
//	EXPECT_EQ(ss.str(), "[[-5, 5], [0, 3]]");
//}

//TEST(DomainMethods, Contains) {
//	Domain d = {{-5, 5}, {0, 3}};
//	Point p1 = {-1, 2};
//	Point p2 = {-10, 2};
//	Point p3 = {-10, 20};
//	Point p4 = {-5, 0};
//	EXPECT_TRUE(d.Contains(p1));
//	EXPECT_FALSE(d.Contains(p2));
//	EXPECT_FALSE(d.Contains(p3));
//	EXPECT_TRUE(d.Contains(p4));
//}

//TEST(DomainMethods, ZoomToPoint) {
//	Domain dom_next = {{-4, 4}, {-3, 2}};
//	Point p = {2, 1};
//	dom_next.ZoomToPoint(dom_next, p, 0.5);
//	Point ref0 = {-1, 3};
//	Point ref1 = {-1, 1.5};
//	EXPECT_EQ(dom_next[0], ref0);
//	EXPECT_EQ(dom_next[1], ref1);
//}

//TEST(ScalarFields, Repr) {
//	F1 f;
//	std::stringstream ss;
//	ss << f;
//	EXPECT_EQ(ss.str(), "x^2 + y^2");
//}

//TEST(ScalarFields, GetDomain) {
//	F1 f;
//	std::stringstream ss;
//	ss << f.GetDomain();
//	EXPECT_EQ(ss.str(), "[[-5, 5], [-5, 5]]");
//}

//TEST(ScalarFields, Eval) {
//	F1 f;
//	EXPECT_EQ(f.Eval(Point {0, 0}), 0);
//	EXPECT_EQ(f.Eval(Point {1, -1}), 2);
//	EXPECT_NEAR(f.Eval(Point {1.1, 3.2}), 11.45, 10e-15);
//	EXPECT_THROW(f.Eval(Point {-6, 0}), std::domain_error);
//}

//TEST(ScalarFieldsOps, Eval) {
//	F1 f;
//	EXPECT_EQ(f(Point {1, -2}), 5);
//}

//TEST(ScalarFields, Gradient) {
//	F1 f;
//	EXPECT_TRUE((f.Gradient(Point {2, -3}) - Point {4, -6}).IsZero());
//	EXPECT_TRUE((f.Gradient(Point {5, 1}) - Point {9.95, 2}).IsZero());
//	EXPECT_TRUE((f.Gradient(Point {5, 5}) - Point {9.95, 9.95}).IsZero());
//	EXPECT_THROW(f.Gradient(Point {6, 5}), std::domain_error);
//}

//class FunctionTest : public ::testing::Test {
//protected:
//	class G1 : public Function {
//	private:
//		double Eval_(double r) {
//			return r*r + 3;
//		}
//	public:
//		G1() : Function("x^2 + 3", Domain {{-4, 4}}) {};
//	};


//	G1 g;
//};

//TEST_F(FunctionTest, Eval) {
//	EXPECT_NEAR(g(-2.5), 9.25, 10e-5);
//	EXPECT_THROW(g(5), std::domain_error);
//}

//TEST_F(FunctionTest, Derivative) {
//	EXPECT_NEAR(g.Derivative(-2.5), -5, 10e-5);
//	EXPECT_THROW(g.Derivative(5), std::domain_error);
//}

//class DirectionFunctionTest : public ::testing::Test {
//protected:
//	class G2 : public ScalarField {
//	private:
//		double Eval_(const Point& p) {
//			return pow(p[0] - 70, 2) + 100 * pow(p[0] - p[1], 2);
//		}

//	public:
//		G2() : ScalarField("(x-70)^2 + 100*(x-y)^2", Domain {{-1000, 1000}, {-1000, 1000}}) {};
//	};

//	G2 g;
//};

//TEST_F(DirectionFunctionTest, Eval) {
//	F1 f;
//	DirectionFunction phi1(&f, Point {-3, 2}, Point {0, 3});
//	EXPECT_EQ(phi1(0.5), 21.25);
//	EXPECT_THROW(phi1(4), std::domain_error);

//	G2 g;
//	DirectionFunction phi2(&g, Point {0, 0}, Point {140, 0});
//	EXPECT_EQ(phi2(0.5), 490000);
//	EXPECT_EQ(phi2(0), 4900);
//}

//TEST_F(DirectionFunctionTest, Derivative) {
//	F1 f;
//	DirectionFunction phi1(&f, Point {-3, 2}, Point {0, 3});
//	// \phi'(\alpha) = 18 \alpha + 12
//	EXPECT_NEAR(phi1.Derivative(0.6), 22.8, 10e-14);

//	G2 g;
//	DirectionFunction phi2(&g, Point {0, 0}, Point {140, 0});
//	// \phi'(\alpha) = 3959200 \alpha - 19600
//	EXPECT_NEAR(phi2.Derivative(0), -19600, 10e-6);
//	EXPECT_NEAR(phi2.Derivative(1), 3939600, 10e-6);
//}

//TEST(FindMinBisect, NonZeroLength) {
//	class G : public Function {
//	private:
//		double Eval_(double r) {
//			return -std::sin(r) + 2;
//		}
//	public:
//		G() : Function("-sin(x) + 2", Domain {{0, M_PI}}) {};
//	};
//	G g;
//	IterResult res = g.FindMinBisect(g.GetDomain()[0][0], g.GetDomain()[0][1], 10e-6);
//	EXPECT_TRUE(res.has_converged);
//	EXPECT_TRUE((res.arg - Point {1.570796}).IsZero(10e-6));
//	EXPECT_NEAR(res.val, 1, 10e-6);
//}

//TEST(FIndMinBiscet, ZeroLength) {
//	class G : public Function {
//	private:
//		double Eval_(double r) {
//			return std::cos(r) + 2*r;
//		}
//	public:
//		G() : Function("cos(x) + 2*x", Domain {{0, M_PI}}) {};
//	};
//	G g;
//	IterResult res = g.FindMinBisect(g.GetDomain()[0][0], g.GetDomain()[0][1], 10e-6);
//	EXPECT_FALSE(res.has_converged);
//}

//TEST(LineSearch, NonZeroLength) {
//	F1 f;
//	EXPECT_NEAR(f.LineSearch(Point {-3, -2}, Point {0, 3}, 10e-6), 0.666666, 10e-6);
//}

//TEST(ConjugateGradient, F1Quadratic) {
//	F1 f;
//	ConjugateGradientParams params;
//	params.x_0 = Point {-4, -4};
//	StopIterCriteria oracle = {new MaxIterCriterion(100), new ValDiffCriterion(10e-10)};
//	// IterResult res = f.ConjugateGradient(&params, oracle, false);
//	IterResult res = f.FindMin(OptMethod::ConjugateGradient, &params, oracle, false);
//	EXPECT_TRUE(res.has_converged);
//	EXPECT_TRUE((res.arg - Point {0, 0}).IsZero(10e-6));
//	EXPECT_NEAR(res.val, 0, 10e-6);
//	EXPECT_EQ(res.n_iter, 2);

//	params.x_0 = Point {-4, 1.3333333357};
//	// res = f.ConjugateGradient(&params, oracle, false);
//	res = f.FindMin(OptMethod::ConjugateGradient, &params, oracle, false);
//	EXPECT_TRUE(res.has_converged);
//	EXPECT_TRUE((res.arg - Point {0, 0}).IsZero(10e-6));
//	EXPECT_NEAR(res.val, 0, 10e-6);
//	EXPECT_EQ(res.n_iter, 2);
//}

//TEST(ConjugateGradient, F2Quadratic) {
//	F2 f;
//	ConjugateGradientParams params;
//	params.x_0 = Point {0, 0};
//	StopIterCriteria oracle = {new MaxIterCriterion(100), new ValDiffCriterion(10e-10)};
//	IterResult res = f.ConjugateGradient(&params, oracle, false);
//	EXPECT_TRUE(res.has_converged);
//	EXPECT_TRUE((res.arg - Point {70, 70}).IsZero(10e-6));
//	EXPECT_NEAR(res.val, 0, 10e-6);
//	EXPECT_EQ(res.n_iter, 3);
//}

//TEST(RandomSearchBernoulli, F1Quadratic) {
//	F1 f;
//	srand(1);
//	RandomSearchBernoulliParams params;
//	params.global_search_prob = 0.4;
//	params.contract_factor = 0.5;
//	StopIterCriteria oracle = {new MaxIterCriterion(10000), new ValDiffCriterion(10e-8)};
//	IterResult res = f.FindMin(OptMethod::RandomSearchBernoulli, &params, oracle, false);
//	// std::cout << "---------------" << std::endl;
//	// std::cout << res.has_converged << std::endl;
//	// std::cout << res.arg << std::endl;
//	// std::cout << res.val << std::endl;
//	// std::cout << res.n_iter << std::endl;
//	EXPECT_TRUE(res.has_converged);
//	EXPECT_TRUE((res.arg - Point {0, 0}).IsZero(10e-4));
//	EXPECT_NEAR(res.val, 0, 10e-6);
//	EXPECT_EQ(res.n_iter, 9870);
//}

//namespace {

//}  // namespace

//int main(int argc, char **argv) {
//  ::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}

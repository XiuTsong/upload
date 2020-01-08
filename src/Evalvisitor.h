#ifndef PYTHON_INTERPRETER_EVALVISITOR_H
#define PYTHON_INTERPRETER_EVALVISITOR_H


#include "Python3BaseVisitor.h"
#include "LargeInteger.h"
#include <iomanip>
#include <map> 
#include <vector>
#include <string>
#include <algorithm>

std::map<std::string,antlrcpp::Any> value ;


class EvalVisitor: public Python3BaseVisitor {

    antlrcpp::Any visitFile_input(Python3Parser::File_inputContext *ctx) override 
    {
        

        return visitChildren(ctx);
    }

    antlrcpp::Any visitFuncdef(Python3Parser::FuncdefContext *ctx) override {
        return visitChildren(ctx);
    }

    antlrcpp::Any visitParameters(Python3Parser::ParametersContext *ctx) override {
        return visitChildren(ctx);
    }

    antlrcpp::Any visitTypedargslist(Python3Parser::TypedargslistContext *ctx) override 
    {
 
        return visitChildren(ctx);
    }

    antlrcpp::Any visitTfpdef(Python3Parser::TfpdefContext *ctx) override 
    {
        return visitChildren(ctx) ;
    }

    antlrcpp::Any visitStmt(Python3Parser::StmtContext *ctx) override 
    {
        if (ctx->simple_stmt()) return visit(ctx->simple_stmt()) ;
        if (ctx->compound_stmt()) return visit(ctx->compound_stmt()) ;
    }

    antlrcpp::Any visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) override 
    { 
        return visit(ctx->small_stmt()) ;
    }

    antlrcpp::Any visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) override 
    {
        if (ctx->expr_stmt()) return visit(ctx->expr_stmt()) ;
        if (ctx->flow_stmt()) return visit(ctx->flow_stmt()) ;
    }

    antlrcpp::Any visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) override 
    {
        //std::cout << "Expr_stmt" << std :: endl ;
        if(ctx->ASSIGN(0))    //判断有没有等号
        {
            int num1 = ctx->testlist().size() ; //num1为testlist总数量
            antlrcpp::Any Tmpr , Tmpl ;
            //std :: cout << num1 << endl ;
            //右结合 每个testlist是一个string类型的vector
            Tmpr = visit(ctx->testlist(num1-1)) ;     //Tmpr为最右边的testlist
            int num2 = Tmpr.as<std::vector<antlrcpp::Any>>().size() ;   //num2为右侧数据的数量
            //std:: cout << num2 << endl ;
            for (int i = num1 - 2 ; i >= 0 ; i--)
            {
                Tmpl = visit(ctx->testlist(i)) ;
                for (int j = 0 ; j < num2 ; ++j)
                {                 
                    antlrcpp::Any tmpl , tmpr ;
                    tmpl = Tmpl.as<std::vector<antlrcpp::Any>>()[j] ;
                    tmpr = Tmpr.as<std::vector<antlrcpp::Any>>()[j] ;
                    //std::cout << tmpl.as<std::string>() << std::endl;
                    //if (tmpr.is<LargeInteger>()) std::cout << "LargeInteger" << std::endl ;
                    if (tmpr.is<std::string>())
                    {
                        if (tmpr.as<std::string>()[0] != '"')   //说明右值是变量
                            value[tmpl.as<std::string>()] = value[tmpr.as<std::string>()] ;
                        else //为字符串
                        value[tmpl.as<std::string>()] = tmpr ;     
                    }       
                    else  //不是变量
                    value[tmpl.as<std::string>()] = tmpr ;
                    //if (value[tmpl.as<std::string>()].is<std::string>())
                    //std::cout <<  value[tmpl.as<std::string>()].as<std::string>() << endl ;
                }
            }
        }
        
        
        return visitChildren(ctx) ;
    }

    antlrcpp::Any visitAugassign(Python3Parser::AugassignContext *ctx) override 
    {
        return visitChildren(ctx);
    }

    antlrcpp::Any visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) override 
    {
        if (ctx->break_stmt()) return visit(ctx->break_stmt()) ;
        if (ctx->continue_stmt()) return visit(ctx->continue_stmt()) ;
        if (ctx->return_stmt()) return visit(ctx->return_stmt()) ; 
    }

     antlrcpp::Any visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

     antlrcpp::Any visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

     antlrcpp::Any visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) override {
        return visitChildren(ctx);
    }

    antlrcpp::Any visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) override 
    {
        if (ctx->if_stmt()) return visit(ctx->if_stmt()) ;
        if (ctx->while_stmt()) return visit(ctx->if_stmt()) ;
        if (ctx->funcdef()) return visit(ctx->funcdef()) ;
    }

    antlrcpp::Any visitIf_stmt(Python3Parser::If_stmtContext *ctx) override   
    {
       /* int numTest , numSuite , numElif ;
        numTest = ctx->test().size() ;
        numSuite = ctx->suite().size() ;
        numElif = ctx->ELIF().size() ;
        antlrcpp::Any tmpIf , tmpContext ;
        tmpIf = visit(ctx->test(0)) ;
        if (tmpIf.is<bool>())
        {
            if(tmpIf.as<bool>()) visit(ctx->suite(0)) ;         
        }
        else if (numElif > 0) 
        {
            for (int i = 1 ; i < numElif + 1 ; ++i)
            {
                tmpIf = visit(ctx->test(i)) ;
                if (tmpIf.is<bool>())
                {
                    if (tmpIf.as<bool>()) visit(ctx->suite(i)) ;
                }
            }
        }
        else if (ctx->else())  visit(ctx->suite(numSuite-1)) ; */
        return visit (ctx->test(0)) ;
    }

    antlrcpp::Any visitWhile_stmt(Python3Parser::While_stmtContext *ctx) override 
    {
       /* antlrcpp::tmp ;
        tmp = ctx->test() ;
        if (tmp.is<bool>())
            while((tmp.as<bool>())) visit(ctx->suite()) ;*/
        return visit (ctx->test()) ;
        
    }

    antlrcpp::Any visitSuite(Python3Parser::SuiteContext *ctx) override 
    {
        return visit(ctx->simple_stmt()) ;
    }

    antlrcpp::Any visitTest(Python3Parser::TestContext *ctx) override 
    {
        
        return visit(ctx->or_test()) ;
    }

    antlrcpp::Any visitOr_test(Python3Parser::Or_testContext *ctx) override 
    {
        antlrcpp::Any tmp ;   
        int num = ctx->and_test().size() ;
        if (num == 1) return visit(ctx->and_test(0)) ;
        else 
        {
            bool flag = false ;
            for (int i = 0 ; i < num ; ++i)
            {
                tmp = visit(ctx->and_test(i)) ;
                if (tmp.is<bool>()) 
                {
                    if (tmp.as<bool>())
                    {
                        flag = true ;
                        break ; 
                    } 
                }   
            }
            return flag ;
        }
        
    }

    antlrcpp::Any visitAnd_test(Python3Parser::And_testContext *ctx) override 
    {
        antlrcpp::Any tmp ;        
        int num = ctx->not_test().size() ;
        if (num == 1) return visit(ctx->not_test(0)) ;
        else 
        {
            bool flag = true ;
            for (int i = 0 ; i < num ; ++i)
            {
                tmp = visit(ctx->not_test(i)) ;
                if (tmp.is<bool>())
                {
                    if (!tmp.as<bool>())
                    {
                        flag = false ;
                        break ;
                    }
                }
            }
            return flag ;
        }
        
    }

    antlrcpp::Any visitNot_test(Python3Parser::Not_testContext *ctx) override 
    {
        if (ctx->comparison()) return visit(ctx->comparison()) ;
        else 
        {
            antlrcpp::Any tmp ;
            bool flag ;
            tmp = visit(ctx->not_test()) ;
            if (tmp.is<bool>())
            {
                flag = !tmp.as<bool>() ;
            }
            return flag ;
        }
    }

    antlrcpp::Any visitComparison(Python3Parser::ComparisonContext *ctx) override 
    {
        
        /*int num = ctx->arith_expr().size() ;
        int num2 = ctx->comp_op().size() ;
        std::cout <<num<<std::endl ;
        std::cout <<num2<<std::endl ;
        antlrcpp::Any tmp1 , tmp2 ;     
        bool flag ;  
        for(int i = 0 ; i < num - 1 ; ++i)
        {      
            tmp1 = visit(ctx->arith_expr(i)) ;
            tmp2 = visit(ctx->arith_expr(i+1)) ;
 
            if (tmp1.is<std::string>())
            {
                if (tmp1.as<std::string>()[0] == '"')   //为string
                {
                    int num = tmp1.as<std::string>().size() ;
                    tmp1 = tmp1.as<std::string>().substr(1 , num-2) ;      //去掉引号
                }
                else //为变量
                {
                    std::string name = tmp1.as<std::string>() ;
                    tmp1 = value.at(name) ;
                }
            }
            if (tmp1.is<bool>()) 
            {
                LargeInteger t ;    // t为0
                if (tmp1.as<bool>())
                {
                    t.p[0] = 1 ;
                    tmp1 = t ;
                }  
                else tmp1 = t ;
            }
            if (tmp2.is<std::string>())
            {
                if (tmp2.as<std::string>()[0] == '"')   //为string
                {
                    int num = tmp2.as<std::string>().size() ;
                    tmp2 = tmp2.as<std::string>().substr(1 , num-2) ;      //去掉引号
                }
                else //为变量
                {
                    std::string name = tmp2.as<std::string>() ;
                    tmp2 = value.at(name) ;
                }
            }
            if (tmp2.is<bool>()) 
            {
                LargeInteger t ;    // t为0
                if (tmp2.as<bool>())
                {
                    t.p[0] = 1 ;
                    tmp2 = t ;
                }  
                else tmp2 = t ;
            }

            int key = visit(ctx->comp_op(i)) ;    //注意
            
            switch (key)
            {      
                case 1 :  //小于
                if (tmp1.is<double>() && tmp2.is<double>())              
                    flag = (tmp1.as<double>() < tmp2.as<double>()) ;
                if (tmp1.is<LargeInteger>() && tmp2.is<LargeInteger>())
                    flag = (tmp1.as<LargeInteger>() < tmp2.as<LargeInteger>()) ;
                if (tmp1.is<std::string>() && tmp2.is<std::string>())
                {
                    int len = min(tmp1.as<std::string>().size(), tmp2.as<std::string>().size()) ;
                    flag = true ;
                    for (int i = 0 ; i < len ; ++i)
                    {
                        if (tmp1.as<std::string>()[i] >= tmp2.as<std::string>()[i])
                        {
                            flag = false ;
                            break ;
                        }                        
                    }
                    if (flag)
                    {
                        if (tmp1.as<std::string>().size() >= tmp2.as<std::string>().size())
                        flag = false ;
                        else flag = true ;
                    }         
                } 

                break ;
                case 2 :  //大于
                if (tmp1.is<double>() && tmp2.is<double>())              
                    flag = (tmp1.as<double>() > tmp2.as<double>()) ;
                if (tmp1.is<LargeInteger>() && tmp2.is<LargeInteger>())
                    flag = (tmp1.as<LargeInteger>() > tmp2.as<LargeInteger>()) ;
                if (tmp1.is<std::string>() && tmp2.is<std::string>())
                {
                    int len = min(tmp1.as<std::string>().size(), tmp2.as<std::string>().size()) ;
                    flag = true ;
                    for (int i = 0 ; i < len ; ++i)
                    {
                        if (tmp1.as<std::string>()[i] <= tmp2.as<std::string>()[i] )
                        {
                            flag = false ;
                            break ;
                        }                        
                    }
                    if (flag)
                    {
                        if (tmp1.as<std::string>().size() <= tmp2.as<std::string>().size())
                        flag = false ;
                        else flag = true ;
                    }         
                }           
                break ;
                case 3 :  //等于
                if (tmp1.is<double>() && tmp2.is<double>())
                    flag = (tmp1.as<double>() == tmp2.as<double>()) ;
                if (tmp1.is<LargeInteger>() && tmp2.is<LargeInteger>())
                    flag = (tmp1.as<LargeInteger>() == tmp2.as<LargeInteger>()) ;
                if (tmp1.is<std::string>() && tmp2.is<std::string>())
                {
                    flag = true ;
                    if (tmp1.as<std::string>().size() != tmp2.as<std::string>().size())
                    flag = false ;
                    else
                    {
                        int len ;
                        len = tmp1.as<std::string>().size() ;
                        for (int i = 0 ; i < len ; ++i)
                        {
                            if (tmp1.as<std::string>()[i] != tmp2.as<std::string>()[i])
                            {
                                flag = false ;
                                break ;
                            }                        
                        }
                    }
                }     
                break ;
                case 4 : //大于等于
                if (tmp1.is<double>() && tmp2.is<double>())
                    flag = (tmp1.as<double>() >= tmp2.as<double>()) ;
                if (tmp1.is<LargeInteger>() && tmp2.is<LargeInteger>())
                    flag = (tmp1.as<LargeInteger>() > tmp2.as<LargeInteger>() || tmp1.as<LargeInteger>() == tmp2.as<LargeInteger>()) ;
                if (tmp1.is<std::string>() && tmp2.is<std::string>())
                {
                    int len = min(tmp1.as<std::string>().size(), tmp2.as<std::string>().size()) ;
                    flag = true ;
                    for (int i = 0 ; i < len ; ++i)
                    {
                        if (tmp1.as<std::string>()[i] < tmp2.as<std::string>()[i])
                        {
                            flag = false ;
                            break ;
                        }                        
                    }
                    if (flag)
                    {
                        if (tmp1.as<std::string>().size() < tmp2.as<std::string>().size())
                        flag = false ;
                        else flag = true ;
                    }         
                }           
                break ;
                case 5 ://小于等于
                if (tmp1.is<double>() && tmp2.is<double>())
                    flag = (tmp1.as<double>() <= tmp2.as<double>()) ;
                if (tmp1.is<LargeInteger>() && tmp2.is<LargeInteger>())
                    flag = (tmp1.as<LargeInteger>() < tmp2.as<LargeInteger>() || tmp1.as<LargeInteger>() == tmp2.as<LargeInteger>()) ;
                if (tmp1.is<std::string>() && tmp2.is<std::string>())
                {
                    int len = min(tmp1.as<std::string>().size(), tmp2.as<std::string>().size()) ;
                    flag = true ;
                    for (int i = 0 ; i < len ; ++i)
                    {
                        if (tmp1.as<std::string>()[i] > tmp2.as<std::string>()[i])
                        {
                            flag = false ;
                            break ;
                        }                        
                    }
                    if (flag)
                    {
                        if (tmp1.as<std::string>().size() > tmp2.as<std::string>().size())
                        flag = false ;
                        else flag = true ;
                    }         
                } 
                break ;
                case 6 ://不等于
                if (tmp1.is<double>() && tmp2.is<double>())
                    flag = (tmp1.as<double>() != tmp2.as<double>()) ;
                if (tmp1.is<LargeInteger>() && tmp2.is<LargeInteger>())
                    flag = !(tmp1.as<LargeInteger>() == tmp2.as<LargeInteger>()) ;
                if (tmp1.is<std::string>() && tmp2.is<std::string>())
                {
                    flag = false ;
                    if (tmp1.as<std::string>().size() != tmp2.as<std::string>().size())
                    flag = true ;
                    else
                    {
                        int len = tmp1.as<std::string>().size() ;
                        for (int i = 0 ; i < len ; ++i)
                        {
                            if (tmp1.as<std::string>()[i] != tmp2.as<std::string>()[i])
                            {
                                flag = true ;
                                break ;
                            }                        
                        }
                    }
                }     
            }
            if (!flag) break ;
            
        }
        return flag ;*/
        
        return visit(ctx->arith_expr(0)) ;
    }

    antlrcpp::Any visitComp_op(Python3Parser::Comp_opContext *ctx) override 
    {
        std::cout << "comp"<<std::endl ;
        int k ;
        if (ctx->LESS_THAN())
        {
            k = 1 ;
            std::cout << "<"<<std::endl ;
        } 
        else if (ctx->GREATER_THAN()) k = 2 ;
        else if (ctx->EQUALS()) k = 3 ;
        else if (ctx->GT_EQ()) k = 4 ;
        else if (ctx->LT_EQ()) k = 5 ;
        else if (ctx->NOT_EQ_2()) k = 6 ;
        return k ;
    }

    antlrcpp::Any visitArith_expr(Python3Parser::Arith_exprContext *ctx) override 
    {
        int num = ctx->term().size() ;
        //std::cout<<"num = "<< num<<std::endl ;
        if (num == 1) return visit(ctx->term(0)) ;
        
        else
        {
            //std::cout << num << std::endl ;
            bool flag ;// 判断符号
            bool flaga = true , flagm = true ;   
            int numa = 0 , numm = 0 ;
            numa = ctx->ADD().size() ;
            numm = ctx->MINUS().size() ;
            size_t ta = 0, tm = 0 ;
            int na = 0 , nm = 0;
            antlrcpp::Any tmp0 , tmp  ;
            // 将name/bool/string转成可运算的量
            tmp0 = visit(ctx->term(0)) ;
            //if (tmp0.is<LargeInteger>()) std::cout << tmp0.as<LargeInteger>() << "=LargeInteger" << std::endl ;
            if (tmp0.is<std::string>() && tmp0.as<std::string>()[0] != '"') //为变量
            {
                string name = tmp0.as<std::string>() ;
                tmp0 = value[name] ;
                //std::cout<<tmp.as<LargeInteger>()<<std::endl ;
            }
            else if (tmp0.is<std::string>() && tmp0.as<std::string>()[0] == '"')
            {             
                int len = tmp0.as<std::string>().size() ;
                tmp0 = tmp0.as<std::string>().substr(0 , len-2) ;   //去后引号
                //std::cout<<tmp.as<std::string>()<<std::endl ;            
            }
            if (tmp0.is<bool>()) 
            {
                LargeInteger t0("0") , t1("1")  ;    // t1为0
                //std::cout << "here" << std::endl ;
                if (tmp0.as<bool>()) tmp0 = t1 ; 
                else tmp0 = t0 ;
                
            }
           // std::cout << "yes?" << std::endl ;
            for (int i = 1 ; i < num ; ++i)
            {
                //std::cout << "yes " << i << std::endl ;
                tmp = visit(ctx->term(i)) ;
                //if (tmp.is<LargeInteger>()) std::cout << "LargeInteger" ;
                //if (tmp.is<double>()) std::cout << "double" ;
                //if (tmp.is<std::string>()) std::cout << "string" ;
                //std::cout<<tmp.as<LargeInteger>()<<std::endl ;
                if (tmp.is<std::string>() && tmp.as<std::string>()[0] != '"') //为变量
                {
                    string name = tmp.as<std::string>() ;
                    tmp = value[name] ;
                    //std::cout<<tmp.as<double>()<<std::endl ;
                }
                if (tmp.is<std::string>() && tmp.as<std::string>()[0] == '"')
                {             
                    int len = tmp.as<std::string>().size() ;
                    if (i < num - 1)
                    tmp = tmp.as<std::string>().substr(1 , len-2) ;      //中间的去掉前后引号
                    else tmp = tmp.as<std::string>().substr(1 , len-1) ;   //最后一个去前引号
                    //std::cout<<tmp.as<std::string>()<<std::endl ;            
                }
                if (tmp.is<bool>()) 
                {
                    LargeInteger t0("0") , t1("1") ;    // t为0
                    if (tmp.as<bool>()) tmp = t1 ;
                    else tmp = t0 ;
                }
                
                if (numa > 0 && na < numa)
                ta = ctx -> ADD(na) -> getSymbol() -> getTokenIndex() ;
                else flaga = false ;
                if (numm > 0 && nm < numm)
                tm = ctx -> MINUS(nm) -> getSymbol() -> getTokenIndex() ;
                else flagm = false ;
                //std::cout << "ta = " << ta <<"tm = " << tm << std:: endl ;
                if (!flaga) flag = false ;
                else if (!flagm) flag = true ;
                else if (ta < tm) flag = true ;
                else flag = false ;
                //std::cout << "flag = " << flag <<std:: endl ;
                if (flag) //加法
                {
                    na++ ;
                    //std::cout << "here? " << flag <<std:: endl ;
                    if (tmp0.is<std::string>() && tmp.is<std::string>())
                        tmp0 = tmp0.as<std::string>() + tmp.as<std::string>() ;
                    if (tmp0.is<double>() && tmp.is<double>())
                        tmp0 = tmp0.as<double>() + tmp.as<double>() ;
                    if (tmp0.is<LargeInteger>() && tmp.is<LargeInteger>())
                    {
                        std::cout << "here? " << tmp.as<LargeInteger>() <<std:: endl ;
                        tmp0 = tmp0.as<LargeInteger>() + tmp.as<LargeInteger>() ;
                    }    
                                         
                        //std :: cout  << "tmp3"<<tmp3 << std::endl ;
                        
                    if (tmp0.is<double>() && tmp.is<LargeInteger>())
                    {                    
                        double x = 0 ;
                        double j = 1 ;
                        //std::cout << "yes?" <<std:: endl ;
                        for (int i = 0 ; i < tmp.as<LargeInteger>().len ; ++i)
                        {                         
                            x += (double)(tmp.as<LargeInteger>().p[tmp.as<LargeInteger>().len-i-1] - '0') * j ;                            
                            j *= 10 ;
                        }
                        //std::cout << tmp.as<LargeInteger>().flag <<std:: endl ; 
                        if(!tmp.as<LargeInteger>().flag)
                        {
                            x *= -1 ;
                            //std::cout << "here" <<std:: endl ; 
                            //std::cout << x <<std:: endl ; 
                        } 
                        tmp0 = tmp0.as<double>() + x ;        
                    }                        
                    if (tmp.is<double>() && tmp0.is<LargeInteger>())
                    {
                        //std::cout<<"inhere"<<std::endl ;
                        double x = 0 ;
                        double j = 1 ;
                        for (int i = 0 ; i < tmp0.as<LargeInteger>().len ; ++i)
                        {
                            x += (double)(tmp0.as<LargeInteger>().p[tmp0.as<LargeInteger>().len - i - 1] -'0') * j ;
                            //std::cout<<tmp0.as<LargeInteger>().p[tmp0.as<LargeInteger>().len - i - 1] -'0'<<std::endl ;       
                            j *= 10 ;
                        }
                        if(!tmp0.as<LargeInteger>().flag) x *= -1 ;
                        
                        tmp0 = tmp.as<double>() + x ;
                    }       
                }
                else
                {
                    nm++ ;
                    //std::cout << "yes?" <<std::endl ;
                    if (tmp0.is<double>() && tmp.is<double>())
                        tmp0 = tmp0.as<double>() - tmp.as<double>() ;
                    if (tmp0.is<LargeInteger>() && tmp.is<LargeInteger>())
                        tmp0 = tmp0.as<LargeInteger>() - tmp.as<LargeInteger>() ;
                    if (tmp0.is<double>() && tmp.is<LargeInteger>())
                    {
                        double x = 0 , j = 1 ; 
                        for (int i = 0 ; i < tmp.as<LargeInteger>().len ; ++i)
                        {                         
                            x += (double)(tmp.as<LargeInteger>().p[tmp.as<LargeInteger>().len - i - 1] - '0') * j ;                            
                            j *= 10 ;
                        }
                        tmp0 = tmp0.as<double>() - x ;
                    }      
                    if (tmp.is<double>() && tmp0.is<LargeInteger>())
                    {
                        
                        int x = 0 , j = 1 ;
                        int length =  tmp0.as<LargeInteger>().len ;
                        for (int i = 0 ; i < length ; ++i)
                        {                         
                            x += (double)(tmp0.as<LargeInteger>().p[length - i - 1] - '0') * j ;                            
                            j *= 10 ;
                        }
                        std::cout << x <<std::endl ;
                        tmp0 = x - tmp.as<double>() ;
                    }            
                }
            }
            return tmp0 ;
        }
        
    }

    antlrcpp::Any visitTerm(Python3Parser::TermContext *ctx) override 
    {
        
        int num = ctx->factor().size() ;
        antlrcpp::Any tmp0 , tmp ;
        tmp0 = visit(ctx->factor(0)) ;
        if (num == 1)
        {
            //if (tmp0.is<LargeInteger>()) std::cout << "LargeInteger" <<std::endl;       
            return tmp0 ;
        } 
        else
        {   
            //处理tmp0
            if (tmp0.is<std::string>() && tmp0.as<std::string>()[0] != '"') //为变量
            {
                string name = tmp0.as<std::string>() ;
                tmp0 = value[name] ;
                // std::cout<<tmp0.as<double>()<<std::endl ;
            }
            if (tmp0.is<std::string>())
            {             
                int len = tmp0.as<std::string>().size() ;         
                tmp0 = tmp0.as<std::string>().substr(1 , len-2) ;      
                std::cout<<tmp0.as<std::string>()<<std::endl ;            
            }
            if (tmp0.is<bool>()) 
            {
                LargeInteger t1("1") , t0("0") ;    // t为0
                if (tmp0.as<bool>())  
                {
                    tmp0 = t1 ; 
                }
                else tmp0 = t0 ;
            }
            //std::cout<<"ok1"<<std::endl ;
            int k = 0 ; //判断符号
            int nums = 0, numd = 0 , numi = 0 , numm = 0 ;
            nums = ctx -> STAR().size() ;
            numd = ctx -> DIV().size() ;
            numi = ctx -> IDIV().size() ;
            numm = ctx -> MOD().size() ;
            size_t ts = 0 , td = 0 , ti = 0 , tm = 0 ; //记录当前符号的位置
            int ns = 0 , nd = 0 , ni = 0 , nm = 0 ; //记录当前符号的下标
            bool flags = true , flagd = true , flagi = true , flagm = true ;
            for (int i = 1 ; i < num ; ++i)
            {
                //预处理
                //std::cout<<"ok2"<<std::endl ;
                tmp = visit(ctx->factor(i)) ;
                if (tmp.is<std::string>() && tmp.as<std::string>()[0] != '"') //为变量
                {
                    string name = tmp.as<std::string>() ;
                    tmp = value[name] ;
                    // std::cout<<tmp.as<double>()<<std::endl ;
                }
                if (tmp.is<std::string>())
                {             
                    int len = tmp.as<std::string>().size() ;                  
                    tmp = tmp.as<std::string>().substr(1 , len-2) ;      //中间的去掉前后引号
                    //std::cout<<tmp.as<std::string>()<<std::endl ;            
                }
                if (tmp.is<bool>()) 
                {
                    LargeInteger t0("0") , t1("1") ;    // t为0
                    if (tmp.as<bool>())
                    {
                        tmp = t1 ;
                    }  
                    else tmp = t0 ;
                } 
                //std::cout<<"ok3"<<std::endl ;
                //判断符号是否有
                if (flags && nums > 0 && ns < nums)
                ts = ctx -> STAR(ns) -> getSymbol() -> getTokenIndex() ;
                else flags = false ;
                if (flagd && numd > 0 && nd < numd)
                td = ctx -> DIV(nd) -> getSymbol() -> getTokenIndex() ;
                else flagd = false ;
                if (flagi && numi > 0 && ni < numi)
                ti = ctx -> IDIV(ni) -> getSymbol() -> getTokenIndex() ;
                else flagi = false ;
                if (flagm && numm > 0 && nm < numm)
                tm = ctx -> MOD(nm) -> getSymbol() -> getTokenIndex() ;
                else flagm = false ;
                //std::cout<<"ok4"<<std::endl ;
                size_t s[4] = {ts, td, ti, tm} ;
                std::sort(s , s+4) ;
                for (int j = 0 ; j < 4 ; ++j)
                {
                    if (s[j] == ts && flags) {k = 1 ; ns++ ; break ;}
                    else if (s[j] == td && flagd) {k = 2 ; nd++ ; break ;}
                    else if (s[j] == ti && flagi) {k = 3 ; ni++ ; break ;}
                    else if (s[j] == tm && flagm) {k = 4 ; nm++ ; break ;}                
                }
                //std::cout << k << std::endl ;
                switch(k)
                {
                    //乘法
                    case 1 :
                            if (tmp0.is<double>() && tmp.is<double>())
                                tmp0 = tmp0.as<double>() * tmp0.as<double>() ;
                            if (tmp0.is<LargeInteger>() && tmp.is<LargeInteger>())
                                tmp0 = tmp0.as<LargeInteger>() * tmp.as<LargeInteger>() ;
                            if (tmp0.is<double>() && tmp.is<LargeInteger>())
                            {
                                double x = 0 , j = 1 ; 
                                for (int i = 0 ; i < tmp.as<LargeInteger>().len ; ++i)
                                {                         
                                    x += (double)(tmp.as<LargeInteger>().p[tmp.as<LargeInteger>().len-i-1] - '0') * j ;                            
                                    j *= 10 ;
                                }
                                tmp0 = tmp0.as<double>() * x ;
                            }      
                            if (tmp.is<double>() && tmp0.is<LargeInteger>())
                            {
                                double x = 0 , j = 1 ; 
                                for (int i = 0 ; i < tmp0.as<LargeInteger>().len ; ++i)
                                {                         
                                    x += (double)(tmp0.as<LargeInteger>().p[tmp0.as<LargeInteger>().len-i-1] - '0') * j ;                            
                                    j *= 10 ;
                                }
                                tmp0 = x * tmp.as<double>() ;
                            }
                            if (tmp0.is<std::string>() && tmp.is<LargeInteger>())
                            {
                                int num = 0 , j = 1 ; 
                                for (int i = 0 ; i < tmp.as<LargeInteger>().len ; ++i)
                                {                         
                                    num += (tmp.as<LargeInteger>().p[tmp.as<LargeInteger>().len-i-1] - '0') * j ;                            
                                    j *= 10 ;
                                }                         
                                std::string tmpString  ; //默认构造函数为空
                                if (num == 0)
                                {
                                    tmp0 =  tmpString ;
                                    //std::cout << tmpString <<std::endl ;
                                    tmpString.insert(0,1,'"') ;   //加上引号
                                    tmpString.append(1,'"') ;
                                } 
                                else
                                {
                                    tmpString = tmp0.as<std::string>() ;
                                    for (int i = 0 ; i < num - 1 ; ++i)
                                    tmpString += tmp0.as<std::string>() ;     
                                    tmpString.insert(0,1,'"') ;   //加上引号
                                    tmpString.append(1,'"') ;
                                    tmp0 = tmpString ;
                                }
                            }
                            if (tmp.is<std::string>() && tmp0.is<LargeInteger>())
                            {
                                int num = 0 , j = 1 ; 
                                for (int i = 0 ; i < tmp0.as<LargeInteger>().len ; ++i)
                                {                         
                                    num += (tmp0.as<LargeInteger>().p[tmp0.as<LargeInteger>().len-i-1] - '0') * j ;                            
                                    j *= 10 ;
                                }
                                std::string tmpString ;
                                if (num == 0)                                
                                    tmp0 = tmpString ;
                                else
                                {
                                    tmpString = tmp.as<std::string>() ;
                                    for (int i = 0 ; i < num - 1 ; ++i)
                                    tmpString += tmp.as<std::string>() ;
                                    tmpString.insert(0,1,'"') ;   //加上引号
                                    tmpString.append(1,'"') ;
                                    tmp0 = tmpString ;
                                }
                            }            
                            break ;
                    //除法
                    case 2 :
                            if (tmp0.is<double>() && tmp.is<double>())
                            //std :: cout <<tmp0.as<double>()<<std::endl ;
                            //std :: cout <<tmp.as<double>()<<std::endl ;
                                tmp0 = tmp0.as<double>() / tmp.as<double>() ;
                            //std :: cout <<tmp0.as<double>()<<std::endl ;
                            if (tmp0.is<LargeInteger>() && tmp.is<LargeInteger>())
                            {
                                double x = 0, y = 0 ,j = 1 , w = 1 ; 
                                for (int i = 0 ; i < tmp0.as<LargeInteger>().len ; ++i)
                                {                         
                                    x += (double)(tmp0.as<LargeInteger>().p[tmp0.as<LargeInteger>().len-i-1] - '0') * j ;                            
                                    j *= 10 ;
                                }
                                for (int i = 0 ; i < tmp.as<LargeInteger>().len ; ++i)
                                {                         
                                    y += (double)(tmp.as<LargeInteger>().p[tmp.as<LargeInteger>().len-i-1] - '0') * w ;                            
                                    w *= 10 ;
                                }
                                tmp0 = x / y ;
                            }
                            else if (tmp0.is<LargeInteger>() && tmp.is<double>()) 
                            {
                                double x = 0, j = 1 ; 
                                for (int i = 0 ; i < tmp0.as<LargeInteger>().len ; ++i)
                                {                         
                                    x += (double)(tmp0.as<LargeInteger>().p[tmp0.as<LargeInteger>().len-i-1] - '0') * j ;                            
                                    j *= 10 ;
                                }
                                tmp0 = x / tmp.as<double>() ;
                            }   
                            else  if (tmp.is<LargeInteger>() && tmp0.is<double>()) 
                            {
                                double  y = 0 , j = 1 ; 
                                
                                tmp0 = tmp0.as<double>() / y ;           
                            }                  
                            break ;
                    //整除
                    case 3 :
                            if (tmp0.is<LargeInteger>() && tmp.is<LargeInteger>())
                                tmp0 = tmp0.as<LargeInteger>() / tmp.as<LargeInteger>() ;                     
                            break ;
                    //取余        
                    case 4 :
                            if (tmp0.is<LargeInteger>() && tmp.is<LargeInteger>())
                                tmp0 = tmp0.as<LargeInteger>() % tmp.as<LargeInteger>() ;
                            break ;               
                }  
            }
            return tmp0 ;
        }    
    }

    antlrcpp::Any visitFactor(Python3Parser::FactorContext *ctx) override 
    {
        if (ctx -> atom_expr()) return visit(ctx->atom_expr()) ;

        else if (ctx -> factor())
        {
            antlrcpp::Any tmp ;
            tmp = visit(ctx->factor()) ;    
            if (ctx->ADD()) return tmp ;
            else //负号
            {
                //std::cout<<"here?"<<std::endl ;
                double x = 0 ;
                if (tmp.is<double>()) tmp = x - tmp.as<double>() ;            
                if (tmp.is<LargeInteger>())
                {
                    //std::cout<<tmp.as<LargeInteger>()<<std::endl ;
                    tmp.as<LargeInteger>().flag = !tmp.as<LargeInteger>().flag ;                   
                    //std::cout<<tmp.as<LargeInteger>()<<std::endl ;
                }
                return tmp ;
            }
        } 
    }

    antlrcpp::Any visitAtom_expr(Python3Parser::Atom_exprContext *ctx) override 
    {
        //std::cout << "Atom_expr" << std::endl; 
        
        if (ctx->trailer())
        { 
            antlrcpp::Any tmp1 , tmp ;
            tmp1 = visit(ctx->atom())  ;        
            tmp = visit(ctx->trailer()) ;
            // std :: cout << "1" << std::endl ;         
            if (tmp1.as<std::string>() == "print")
            {
                int num = tmp.as<std::vector<antlrcpp::Any>>().size() ;
                for (int i = 0 ; i < num ; ++i)
                {
                    antlrcpp::Any tmp2 ;
                    // std :: cout << "2" << std::endl ;
                    tmp2 = tmp.as<std::vector<antlrcpp::Any>>()[i] ;
                    if (tmp2.is<std::string>())
                    {         
                                  
                        if (tmp2.as<std::string>() == "None" )  //为None
                        std :: cout << "None" ;
                        else if (tmp2.as<std::string>()[0]=='"')
                        {  
                            int n = tmp2.as<std::string>().size() ;
                            tmp2 = tmp2.as<std::string>().substr(1, n-2) ;
                            std :: cout << tmp2.as<std::string>() ;               
                        }
                                            
                        else  //为变量
                        {
                            //std :: cout << tmp2.as<std::string>() << std::endl ;   
                            if (value[tmp2.as<std::string>()].is<std::string>())
                            {
                               // std::cout <<"Yes" << std::endl ;
                                // std::cout << tmp2.as<std::string>() << std::endl;
                                std :: string tmpString = value[(tmp2.as<std::string>())].as<std::string>() ;
                                int n = value[(tmp2.as<std::string>())].as<std::string>().size() ;
                                //std :: cout << n << std::endl ;
                                tmpString = tmpString.substr(1, n-2) ;
                                std :: cout << tmpString ;
                            }
                            else if (value.at(tmp2.as<std::string>()).is<double>())
                            std :: cout << std::fixed << std::setprecision(6) << value.at(tmp2.as<std::string>()).as<double>() ;
                            else if (value.at(tmp2.as<std::string>()).is<LargeInteger>())
                            std :: cout << value.at(tmp2.as<std::string>()).as<LargeInteger>() ;
                            else if (value.at(tmp2.as<std::string>()).is<bool>())
                            {
                                if (value.at(tmp2.as<std::string>()).as<bool>())
                                std :: cout << "True" ;
                                else std :: cout << "False" ;
                            }
                        }                                          
                    } 

                    else if (tmp2.is<double>())
                    {
                       // std ::cout << "isDouble" <<std::endl ;
                        std::cout << std::fixed << std::setprecision(6) << tmp2.as<double>() ;
                    }
                    else if (tmp2.is<LargeInteger>())  
                    {
                        //std ::cout << "isLargeInteger" <<std::endl ;
                        std::cout << tmp2.as<LargeInteger>() ; 
                    } 
                    else if (tmp2.is<bool>())
                    {
                        if (tmp2.as<bool>()) std::cout << "True" ;
                        else std::cout << "False" ;
                    }
                    std:: cout << " " ;   
                }              
                std::cout << std::endl ; 
            }                
        }        
        return visit(ctx->atom())  ;
    }

    antlrcpp::Any visitTrailer(Python3Parser::TrailerContext *ctx) override 
    {
        //std::cout << "Trailer" << std::endl ;
       return visit(ctx->arglist());
    }

    antlrcpp::Any visitAtom(Python3Parser::AtomContext *ctx) override 
    {
        //std::cout << "Atom" << std::endl ;
        std::string tmpString ;
        if (ctx->NAME()) 
        {       
            tmpString = ctx -> NAME() -> toString() ;
            return tmpString ;
            //std::cout << tmpString ;
        }
        if (ctx->STRING(0)) 
        {
            int n = ctx->STRING().size() ;
            for (int i = 0 ; i < n  ; ++i)
            {
                tmpString += ctx->STRING(i)->toString() ;
            }
        //    if (tmpString[n-1] == '"') tmpString.erase(n-1) ;
            return tmpString ;
        } 
        if (ctx->NUMBER())
        { 
            antlrcpp::Any tmp ;
            tmp = ctx->NUMBER()->toString() ;
            //std::cout << tmp.as<std::string>() <<std::endl;
            int n = tmp.as<std::string>().size() ;
            //std::cout << n <<std::endl;
            int num ; //double的整数位数
            bool flag = false ;
            for (int i = 0 ; i < n ; ++i)
            {
                if (tmp.as<std::string>()[i] == '.')
                {
                    flag = true ;
                    num = i ;
                    break ;
                }         
            }
            //std::cout << flag << std::endl ;
            if (flag) //为double
            {
                //std :: cout <<"ok" <<std::endl ;
                double tmp1 = 0 ;
                //std :: cout <<"n="<<n<< " num=" <<num << std::endl ;
                double j = 1 ;
                for (int i = 0 ; i < num ; ++i)
                {               
                    tmp1 += (tmp.as<std::string>()[num - i - 1] - '0') * j ; 
                    j = j * 10.0 ; 
                    //std::cout <<j  << " " <<std::endl;
                } //整数部分
                //
                j = 10 ;
                for (int i = num + 1 ; i < n ;++i )
                {                
                    tmp1 += (tmp.as<std::string>()[i] - '0') / j ;  
                   // std::cout <<  (tmp.as<std::string>()[i] - '0') / j << " " <<std::endl;
                    j *= 10 ;                 
                } 
                return tmp1 ;                
            }
            else //为LargeInteger
            {  
                
                LargeInteger tmp2(n) ;
                //tmp2 = 12345 ;

                //std :: cout << tmp2.len <<std::endl;
                for (int i = 0 ; i < n ; ++i)
                {
                    
                    tmp2.p[i] = tmp.as<std::string>()[i] ;
                    //std::cout <<  tmp2.p[i] <<" " ;
                } 
                //std ::cout << tmp2.len ;
                //std::cout << tmp2 <<" " << std::endl ;                 
                return tmp2 ;
            }
        } 
        if (ctx->NONE()) 
        {
            tmpString =  ctx -> NONE() -> toString();
            return tmpString ;
        }
        if (ctx->TRUE())        
        {   
            bool tmp = true ;   
            return tmp ;
        }
        if (ctx->FALSE()) 
        { 
            bool tmp = false ;
            return tmp ;
        }         
        
    }

    antlrcpp::Any visitTestlist(Python3Parser::TestlistContext *ctx) override 
    {
        int n = ctx->test().size() ;
        std::vector <antlrcpp::Any> t ;
        for (int i = 0 ; i < n ; ++i)
        {
            antlrcpp::Any tmp ;
            tmp = visit (ctx->test(i)) ;
            t.push_back(tmp) ;
        }
        return t ;
    }

    antlrcpp::Any visitArglist(Python3Parser::ArglistContext *ctx) override 
    {
        //std::cout << "Arglist" << std :: endl ;
        int n = ctx->argument().size() ;
        std::vector <antlrcpp::Any> argue ;
        for (int i = 0 ; i < n ; ++i)
        {
            antlrcpp::Any tmp ;
            tmp = visit (ctx->argument(i)) ;          
            argue.push_back(tmp) ;
        }
        return argue ;
    }

    antlrcpp::Any visitArgument(Python3Parser::ArgumentContext *ctx) override 
    {
        //std::cout << "Argument" << std::endl ;
        return visit(ctx->test());
    }
} ;


#endif //PYTHON_INTERPRETER_EVALVISITOR_H
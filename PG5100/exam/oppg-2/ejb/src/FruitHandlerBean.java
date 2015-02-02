import entity.Fruit;
import entity.Salad;

import javax.ejb.EJB;
import javax.ejb.Stateless;
import javax.persistence.*;
import java.util.List;

@Stateless(name = "FruitHandlerEJB")
@PersistenceContext
public class FruitHandlerBean {
    private EntityManagerFactory managerFactory;
    private EntityManager manager;
    private EntityTransaction transaction;

    @EJB
    UserHandlerBean userHandlerBean;

    public FruitHandlerBean() {
        managerFactory = Persistence.createEntityManagerFactory("KimbanPUnit");
        manager = managerFactory.createEntityManager();
        transaction = manager.getTransaction();
    }

    //Gets all fruit variants from the database
    //These are used to display the various fruit options in saladmanager.xhtml
    public List<Fruit> getAllFruitVariants() {
        Query query = manager.createQuery("SELECT f FROM Fruit f");

        return query.getResultList();
    }

    public List<Salad> getUserSalads() {
        return userHandlerBean.getUser().getSalads();
    }
}
